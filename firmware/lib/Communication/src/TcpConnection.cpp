#include "TcpConnection.h"
#include <errno.h>
#include <lwip/sockets.h>
#include <string.h>

void TcpConnection::begin(const char* host, uint16_t port, Protocol::Role role, ConnectionSettings settings) {
    host_ = host;
    port_ = port;
    role_ = role;
    settings_ = settings;
    lastAttempt_ = millis() - settings_.retryMs;
}

void TcpConnection::resolveHost(void* context) {
    auto* self = static_cast<TcpConnection*>(context);
    IPAddress address;
    bool ok = WiFi.hostByName(self->host_, address) == 1;
    self->resolvedAddress_ = address;
    self->dnsStatus_.store(ok ? 2 : 3);
    vTaskDelete(nullptr);
}

void TcpConnection::disconnect() {
    if (state_ != State::Disconnected) { Serial.println("TCP disconnected; retry scheduled"); }
    client_.stop();
    state_ = State::Disconnected;
    input_.reset();
    outputSize_ = outputSent_ = 0;
    lastAttempt_ = millis();
}

void TcpConnection::update(uint32_t now, bool wifiOnline) {
    if (!wifiOnline) {
        if (state_ != State::Disconnected) { disconnect(); }
        return;
    }
    if (state_ != State::Disconnected && !client_.connected()) { disconnect(); }
    if (state_ == State::Ready && millis() - lastReceivedAt_ >= 15000UL) {
        Serial.println("TCP receive timeout");
        disconnect();
    }
    now = millis();
    if (state_ == State::Disconnected) {
        IPAddress address;
        int dns = dnsStatus_.load();
        if (dns == 1) { return; }
        if (dns == 3) {
            Serial.printf("DNS failed: %s\n", host_);
            dnsStatus_.store(0);
            lastAttempt_ = now;
            return;
        }
        if (dns == 2) {
            address = resolvedAddress_;
            dnsStatus_.store(0);
        } else {
            if (now - lastAttempt_ < settings_.retryMs) { return; }
            if (!address.fromString(host_)) {
                Serial.printf("DNS resolving: %s\n", host_);
                dnsStatus_.store(1);
                if (xTaskCreate(resolveHost, "iot-dns", 4096, this, 1, nullptr) != pdPASS) {
                    dnsStatus_.store(3);
                }
                return;
            }
        }
        lastAttempt_ = now;
        Serial.printf("TCP connecting: %s:%u\n", host_, port_);
        if (!client_.connect(address, port_, settings_.connectTimeoutMs)) {
            Serial.println("TCP connect failed; check server, address, port and firewall");
            lastAttempt_ = millis();
            return;
        }
        client_.setNoDelay(true);
        state_ = State::Registering;
        registeredAt_ = millis();
        char line[80];
        if (!Protocol::ProtocolCodec::registration(role_, line, sizeof(line)) || !sendLine(line)) { disconnect(); }
    }
    if (state_ == State::Ready && millis() - lastPingAt_ >= 5000UL && outputSize_ == 0) {
        if (sendLine("PING\n")) { lastPingAt_ = millis(); }
    }
    flushTransmit(millis());
    if (state_ == State::Registering && millis() - registeredAt_ >= settings_.registerTimeoutMs) {
        Serial.println("TCP registration timeout; expected OK for this role");
        disconnect();
    }
}

bool TcpConnection::sendLine(const char* line) {
    if (state_ == State::Disconnected || outputSize_ != 0) { return false; }
    size_t length = strlen(line);
    if (!length || length >= sizeof(output_)) { return false; }
    memcpy(output_, line, length);
    outputSize_ = length;
    outputSent_ = 0;
    txStartedAt_ = millis();
    flushTransmit(txStartedAt_);
    return state_ != State::Disconnected;
}

void TcpConnection::flushTransmit(uint32_t now) {
    if (!outputSize_) { return; }
    // A bounded pending message and nonblocking writes keep LED timing responsive.
    int written = ::send(client_.fd(), output_ + outputSent_, outputSize_ - outputSent_, MSG_DONTWAIT);
    if (written > 0) {
        outputSent_ += static_cast<size_t>(written);
        if (outputSent_ == outputSize_) { outputSize_ = outputSent_ = 0; }
    } else if (written == 0 || (errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR)) {
        disconnect();
    }
    if (outputSize_ && now - txStartedAt_ >= static_cast<uint32_t>(settings_.connectTimeoutMs)) { disconnect(); }
}

bool TcpConnection::nextMessage(Protocol::Message& message) {
    if (state_ == State::Disconnected) { return false; }
    size_t budget = Protocol::MAX_LINE_BYTES + 2;
    while (budget-- && client_.available()) {
        int byte = client_.read();
        if (byte < 0) { break; }
        Protocol::LineBuffer::Result result = input_.push(static_cast<char>(byte));
        if (result == Protocol::LineBuffer::Result::Error) { disconnect(); return false; }
        if (result != Protocol::LineBuffer::Result::Ready) { continue; }
        if (!Protocol::ProtocolCodec::parse(input_.line(), message)) {
            Serial.println("Invalid server message; disconnecting");
            disconnect();
            return false;
        }
        lastReceivedAt_ = millis();
        if (message.kind == Protocol::Kind::Pong && state_ == State::Ready) { continue; }
        if (message.kind == Protocol::Kind::Error) {
            Serial.print("Server error: ");
            Serial.println(message.errorCode);
            disconnect();
            return false;
        }
        if (state_ == State::Registering) {
            if (message.kind != Protocol::Kind::Ok || message.role != role_) { disconnect(); return false; }
            state_ = State::Ready;
            lastPingAt_ = lastReceivedAt_ = millis();
            Serial.println("TCP registered");
            continue;
        }
        return true;
    }
    return false;
}
