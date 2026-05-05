#include "WebServerDriver.h"
#include "Config/WifiConfig.h"

namespace Drivers {
    WebServerDriver::WebServerDriver() : server_(new WebServer(80)){
          if (!LittleFS.begin()) {
        Serial.println("Erro ao montar LittleFS");
        return;
    }
  
    }

    void WebServerDriver::tick() {
        server_->handleClient();
    }

    void WebServerDriver::beginDashboard()
    {
        delete server_;
        server_ = new WebServer(80);
        this->setupDashboardRoutes();
        server_->begin();
    }
    void WebServerDriver::beginConfigPortal(WifiDriver& wifi)
    {
        delete server_;
        server_ = new WebServer(80);
        this->setupConfigRoutes(wifi);
        server_->begin();
    }
    auto WebServerDriver::consumePendingConfig() -> Config::WifiConfig
    {
        hasPendingConfig_ = 0;
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
    }
    void WebServerDriver::setupConfigRoutes(WifiDriver& wifi)
    {
        server_->on("/api/networks", HTTP_GET, [this]() -> void
            {
            int16_t scanned_wifi = WiFi.scanNetworks();
            String json = "[";
            for (uint8_t i = 0; i < scanned_wifi; ++i)
            {
                if (i > 0) {
                    json += ",";
                }
                json += "{";
                json += R"("ssid":")" + WiFi.SSID(i) + "\",";
                json += "\"rssi\":" + String(WiFi.RSSI(i));
                json += "}";
            }
            json += "]";
            server_->send(200, "application/json", json);
        });
        server_->on("/api/connect", HTTP_POST, [this]()-> void
            {
            String ssid = server_->arg("ssid");
            String psw = server_->arg("password");

            strncpy(pendingConfig_.ssid, ssid.c_str(), sizeof(pendingConfig_.ssid));
            strncpy(pendingConfig_.psw, psw.c_str(), sizeof(pendingConfig_.psw));

            hasPendingConfig_ = true;

            server_->send(200, "application/json", R"({"status":"ok"})");
        });
    }
}
