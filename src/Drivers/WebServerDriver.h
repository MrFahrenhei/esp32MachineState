#pragma once
#include <WebServer.h>
#include "Config/WifiConfig.h"
#include <LittleFS.h>
#include <memory>
#include "WifiDriver.h"

namespace Drivers {
    class WebServerDriver {
    public:
        WebServerDriver();
        ~WebServerDriver() = default;

        WebServerDriver(const WebServerDriver&) = delete;
        auto operator=(const WebServerDriver&) -> WebServerDriver& = delete;

        WebServerDriver(WebServerDriver&&) = delete;
        auto operator=(WebServerDriver&&) -> WebServerDriver& = delete;

        void tick() const;
        void beginDashboard();
        void beginConfigPortal();
        [[nodiscard]] auto hasPendingConfig() const -> bool;
        auto consumePendingConfig() -> Config::WifiConfig;

        [[nodiscard]] auto hasResetWifiRequest() const -> bool;
        void consumeResetWifiRequest();
    private:
        void setupDashboardRoutes();
        void setupConfigRoutes();

        bool hasPendingConfig_{false};
        bool hasResetWifiRequest_{false};

        std::unique_ptr<WebServer> server_{nullptr};

        Config::WifiConfig pendingConfig_{};
    };
}


