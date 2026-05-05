#pragma once
#include <WebServer.h>
#include "Config/WifiConfig.h"
#include "WifiDriver.h"
#include <LittleFS.h>

namespace Drivers {
    class WebServerDriver {
    public:
        WebServerDriver();
        void tick();
        void beginDashboard();
        void beginConfigPortal(WifiDriver& wifi);
        uint8_t hasPendingConfig_ = 0;
        auto consumePendingConfig() -> Config::WifiConfig;
    private:
        void setupDashboardRoutes();
        void setupConfigRoutes(WifiDriver& wifi);

        WebServer* server_;

        Config::WifiConfig pendingConfig_;
    };
}


