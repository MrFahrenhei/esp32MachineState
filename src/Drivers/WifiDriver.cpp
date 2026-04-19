#include "WifiDriver.h"
namespace Drivers {
    void WifiDriver::startStation(const char *ssid, const char *psw) {
        WiFiClass::mode(WIFI_STA);
        WiFi.begin(ssid,psw);
    }

    void WifiDriver::startAccessPoint(const char *ssid, const char *psw) {
        WiFiClass::mode(WIFI_AP);
        WiFi.softAP(ssid, psw);
    }

    bool WifiDriver::waitForConnection(unsigned long timeoutMs) {
        const unsigned long start = millis();
        while (WiFi.status() != WL_CONNECTED && millis() - start < timeoutMs) {
            delay(300);
            Serial.print(".");
        }
            Serial.println(".");
        return WiFi.status() == WL_CONNECTED;
    }
    IPAddress WifiDriver::localIP() const
    {
        if (WiFi.getMode() == WIFI_AP)
            return WiFi.softAPIP();

        return WiFi.localIP();
    }

    void WifiDriver::disconnect(bool eraseConfig) {
        WiFi.disconnect(eraseConfig, eraseConfig);
    }
}
