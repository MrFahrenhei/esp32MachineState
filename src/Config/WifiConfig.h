#pragma once
#include <cstdint>
namespace Config {
    struct WifiConfig {
        char ssid[32]{};
        char psw[32]{};
        uint8_t configured{0};
        void clear() {
            ssid[0] = '\0';
            psw[0] = '\0';
            configured = 0;
        }
    };
}