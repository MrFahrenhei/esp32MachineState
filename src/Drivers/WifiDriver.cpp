#include "WifiDriver.h"
namespace Drivers {
    void WifiDriver::startStation(const char *ssid, const char *psw) {
        WiFiClass::mode(WIFI_STA);
        WiFi.begin(ssid,psw);
    }

    void WifiDriver::startAccessPoint(const char *ssid, const char *psw) {
        WiFiClass::mode(WIFI_AP);
        WiFi.begin(ssid, psw);
    }

    bool WifiDriver::waitForConnection(unsigned long timeoutMs) {
        const unsigned long start = millis();
        while (WiFiClass::status() != WL_CONNECTED && millis() - start < timeoutMs) {
            delay(300);
            Serial.print(".");
        }
            Serial.println(".");
        return WiFiClass::status() == WL_CONNECTED;
    }
    void WifiDriver::disconnect(bool eraseConfig) {
        WiFi.disconnect(eraseConfig, eraseConfig);
    }
}
