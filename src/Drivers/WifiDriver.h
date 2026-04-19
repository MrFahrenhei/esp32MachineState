#pragma once
#include <WiFi.h>
namespace Drivers {
    class WifiDriver {
    public:
        void startStation(const char* ssid, const char* psw);
        void startAccessPoint(const char* ssid, const char* psw);
        bool waitForConnection(unsigned long timeoutMs);
        IPAddress localIP() const;
        void disconnect(bool eraseConfig);
    };
}
