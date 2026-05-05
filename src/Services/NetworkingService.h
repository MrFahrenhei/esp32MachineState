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
        Drivers::WifiDriver& wifi_;
        Drivers::WebServerDriver& webServer_;

        static constexpr auto default_ap_ssid = "AvetoolsSuporte";
        static constexpr auto default_ap_psw = "osuporte";
    };
}
