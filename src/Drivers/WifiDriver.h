#pragma once
#include <WiFi.h>
namespace Drivers {
    class WifiDriver {
    public:
        void startStation(const char* ssid, const char* psw);
        void startAccessPoint(const char* ssid, const char* psw);
        auto waitForConnection(unsigned long timeoutMs) -> bool;
        [[nodiscard]] auto localIP() const -> IPAddress;
        void disconnect(bool eraseConfig);
    };
}
