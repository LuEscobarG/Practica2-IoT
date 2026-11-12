#pragma once

// Copy to Config.local.h and fill in your network settings. Never commit credentials.
#define IOT_WIFI_SSID "YOUR_WIFI_SSID"
#define IOT_WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#define IOT_SERVER_HOST "192.168.1.100"
#define IOT_SERVER_PORT 5000

// A reachable IPv4 address or DNS hostname; no tcp:// prefix or path.
// Keep the safety timeout short; increase only if measured network jitter requires it.
#ifndef IOT_COMMAND_TIMEOUT_MS
#define IOT_COMMAND_TIMEOUT_MS 2000
#endif
