#pragma once
#include <Arduino.h>
#include "TcpConnection.h"
#if __has_include("Config.local.h")
#include "Config.local.h"
#else
#include "Config.example.h"
#warning "Configure Config.local.h before uploading to hardware"
#endif
#ifndef IOT_COMMAND_TIMEOUT_MS
#define IOT_COMMAND_TIMEOUT_MS 2000
#endif
#ifndef IOT_CONNECT_TIMEOUT_MS
#define IOT_CONNECT_TIMEOUT_MS 3000
#endif
namespace Config {
constexpr uint8_t TRIG_PIN = 5, ECHO_PIN = 18;
constexpr uint8_t RED_PIN = 25, YELLOW_PIN = 26, BLUE_PIN = 27;
constexpr uint32_t SERIAL_BAUD = 115200, SAMPLE_MS = 250;
constexpr uint32_t COMMAND_TIMEOUT_MS = IOT_COMMAND_TIMEOUT_MS;
constexpr ConnectionSettings TCP_SETTINGS = {2000, 5000, IOT_CONNECT_TIMEOUT_MS};
}
