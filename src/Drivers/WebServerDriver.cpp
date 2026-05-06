#include "WebServerDriver.h"
#include "Config/WifiConfig.h"

namespace Drivers {
    WebServerDriver::WebServerDriver(): server_(std::make_unique<WebServer>(80)){
        if (!LittleFS.begin()) {
            Serial.println("Erro ao montar LittleFS");
            return;
        }
    }

    void WebServerDriver::tick() const {
        server_->handleClient();
    }
    auto WebServerDriver::hasPendingConfig() const -> bool {
        return hasPendingConfig_;
    }
    void WebServerDriver::beginDashboard()
    {
        server_ = std::make_unique<WebServer>(80);
        this->setupDashboardRoutes();
        server_->begin();
    }
    void WebServerDriver::beginConfigPortal()
    {
        server_ = std::make_unique<WebServer>(80);
        this->setupConfigRoutes();
        server_->begin();
    }
    auto WebServerDriver::consumePendingConfig() -> Config::WifiConfig
    {
        hasPendingConfig_ = false;
        return pendingConfig_;
    }

    void WebServerDriver::setupDashboardRoutes() {
        server_->on("/", HTTP_GET, [this]() -> void {
            File file = LittleFS.open("/index.html", "r");
            if (!file) {
                server_->send(404, "text/plain", "Arquivo index.html não encontrado");
                return;
            }

            server_->streamFile(file, "text/html");
            file.close();
        });
        server_->on("/reset-wifi", HTTP_POST, [this]() -> void {
            Serial.println("Reset WiFi solicitado via HTTP");
            hasResetWifiRequest_ = true;
            server_->send(200, "application/json", R"({"status":"reset_requested"})");
        });
    }
    void WebServerDriver::setupConfigRoutes()
    {
        server_->on("/", HTTP_GET, [this]() -> void {
           File file = LittleFS.open("/configRoute.html", "r");
           if (!file) {
               server_->send(404, "text/plain", "Arquivo configRoute.html não encontrado");
               return;
           }
           server_->streamFile(file, "text/html");
           file.close();
       });
        server_->on("/", HTTP_POST, [this]()-> void
            {
            String ssid = server_->arg("ssid");
            String psw = server_->arg("password");

            std::strncpy(pendingConfig_.ssid, ssid.c_str(), sizeof(pendingConfig_.ssid) - 1);
            pendingConfig_.ssid[sizeof(pendingConfig_.ssid) - 1] = '\0';

            std::strncpy(pendingConfig_.psw, psw.c_str(), sizeof(pendingConfig_.psw) - 1);
            pendingConfig_.psw[sizeof(pendingConfig_.psw) - 1] = '\0';

            pendingConfig_.configured = true;
            hasPendingConfig_ = true;

            server_->send(200, "application/json", R"({"status":"ok"})");
        });
    }
    auto WebServerDriver::hasResetWifiRequest() const -> bool {
        return hasResetWifiRequest_;
    }

    void WebServerDriver::consumeResetWifiRequest() {
        hasResetWifiRequest_ = false;
    }
}
