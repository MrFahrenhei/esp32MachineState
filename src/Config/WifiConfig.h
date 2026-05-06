#pragma once
#include <cstdint>
#include <cstring>

namespace Config {
    struct WifiConfig {
        char ssid[32]{};
        char psw[32]{};
        bool configured{false};
        void clear() {
            ssid[0] = '\0';
            psw[0] = '\0';
            configured = false;
        }
        void setSsid(const char* value) {
            std::strncpy(ssid, value, sizeof(ssid) - 1);
            ssid[sizeof(ssid) - 1] = '\0';
        }

        void setPsw(const char* value) {
            std::strncpy(psw, value, sizeof(psw) - 1);
            psw[sizeof(psw) - 1] = '\0';
        }
    };
}