#pragma once
#include "../Drivers/WifiDriver.h"
#include "Drivers/WebServerDriver.h"

namespace Services {
    class NetworkingService {
    public:
        NetworkingService(
            Drivers::WifiDriver& wifi,
            Drivers::WebServerDriver& webServer
            );
        void start();
    private:
        Drivers::WifiDriver& _wifi;
        Drivers::WebServerDriver& _webServer;
    private:
        static constexpr auto DEFAULT_AP_SSID = "AvetoolsSuporte";
        static constexpr auto DEFAULT_AP_PSW = "osuporte";
    };
}
