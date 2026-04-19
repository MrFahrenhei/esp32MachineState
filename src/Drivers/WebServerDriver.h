#pragma once
#include <WebServer.h>
#include <LittleFS.h>
#include "WifiDriver.h"
#include "Config/Config.h"

namespace Drivers {
    class WebServerDriver {
    public:
        WebServerDriver();
        void tick();
        void beginDashboard();
        void beginConfigPortal(WifiDriver& wifi);
        uint8_t _hasPendingConfig = false;
        Config::WifiConfig consumePendingConfig();
    private:
        void setupDashboardRoutes();
        void setupConfigRoutes(WifiDriver& wifi);
    private:
        WebServer* _server;
        Config::WifiConfig _pendingConfig;
    };
}


