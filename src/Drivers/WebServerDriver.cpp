//
// Created by beraldo on 17/04/2026.
//

#include "WebServerDriver.h"

namespace Drivers {
    WebServerDriver::WebServerDriver()
    {
        _server = new WebServer(80);
    }

    void WebServerDriver::tick() {
        _server->handleClient();
    }

    void WebServerDriver::beginDashboard()
    {
        delete _server;
        _server = new WebServer(80);
        this->setupDashboardRoutes();
        _server->begin();
    }
    void WebServerDriver::beginConfigPortal(WifiDriver& wifi)
    {
        delete _server;
        _server = new WebServer(80);
        this->setupConfigRoutes(wifi);
        _server->begin();
    }
    Config::WifiConfig WebServerDriver::consumePendingConfig()
    {
        this->_hasPendingConfig = false;
        return _pendingConfig;
    }

    void WebServerDriver::setupDashboardRoutes()
    {
        _server->serveStatic("/", LittleFS, "/");
        _server->onNotFound([this]()
        {
            File file = LittleFS.open("/index.html", "r");
            if (!file)
            {
                _server->send(404, "text/plain", "index.html nao encontrado");
                return;
            }
            _server->streamFile(file, "text/html");
            file.close();
        });
    }
    void WebServerDriver::setupConfigRoutes(WifiDriver& wifi)
    {
        _server->on("/api/networks", HTTP_GET, [this]()
        {
            int n = WiFi.scanNetworks();
            String json = "[";
            for (int i = 0; i < n; ++i)
            {
                if (i > 0) json += ",";
                json += "{";
                json += "\"ssid\":\"" + WiFi.SSID(i) + "\",";
                json += "\"rssi\":" + String(WiFi.RSSI(i));
                json += "}";
            }
            json += "]";
            _server->send(200, "application/json", json);
        });
        _server->on("/api/connect", HTTP_POST, [this, &wifi]()
        {
            String ssid = _server->arg("ssid");
            String psw = _server->arg("password");

            strncpy(_pendingConfig.ssid, ssid.c_str(), sizeof(_pendingConfig.ssid));
            strncpy(_pendingConfig.psw, psw.c_str(), sizeof(_pendingConfig.psw));

            _hasPendingConfig = true;

            _server->send(200, "application/json", "{\"status\":\"ok\"}");
        });
    }
}
