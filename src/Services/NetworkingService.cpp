#include "NetworkingService.h"

namespace Services {
    NetworkingService::NetworkingService(Drivers::WifiDriver& wifi, Drivers::WebServerDriver& webServer):
    _wifi(wifi), _webServer(webServer){}
    void NetworkingService::start() {
        _wifi.startAccessPoint(DEFAULT_AP_SSID, DEFAULT_AP_PSW);
        _webServer.beginConfigPortal(_wifi);
        Serial.print("IP: ");
        Serial.println(_wifi.localIP());
    }
}
