#include "NetworkingService.h"

namespace Services {
    NetworkingService::NetworkingService(Drivers::WifiDriver& wifi, Drivers::WebServerDriver& webServer):
    wifi_(wifi), webServer_(webServer){}
    void NetworkingService::start() {
        wifi_.startAccessPoint(default_ap_ssid, default_ap_psw);
        webServer_.beginConfigPortal();
        Serial.print("IP: ");
        Serial.println(wifi_.localIP());
    }
}
