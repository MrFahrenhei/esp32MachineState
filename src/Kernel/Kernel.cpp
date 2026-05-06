#include "Kernel.h"

Kernel::Kernel(): memoryConfigRepository_(preferencesStorage_), networkingService_(wifi_, webServer_) {
    Serial.println("Construct do kernel");
}

void Kernel::boot(){
    Serial.println("Boot do kernel");
    this->loadNetworkingConfiguration();
    Serial.print("Status atual é ");
    Serial.println(config_.wifiConfig.configured);

    if (config_.wifiConfig.configured == false) {
        Serial.println("Não está configurado Wifi");
        this->networkConfigurationPortal();
    }else {
        Serial.print("Está configurado no wifi: ");
        Serial.println(config_.wifiConfig.ssid);
        this->enterWifi();
    }
}

void Kernel::tick() {
    switch (state_) {
    case State::ConfigPortal:
        {
            webServer_.tick();
            Serial.println("Is configPortal");
            if (webServer_.hasPendingConfig())
            {
                Config::WifiConfig new_config = webServer_.consumePendingConfig();
                wifi_.disconnect(false);
                wifi_.startStation(new_config.ssid, new_config.psw);
                if (wifi_.waitForConnection(10000))
                {
                    Serial.println("New wifi connection established");
                    config_.wifiConfig = new_config;
                    memoryConfigRepository_.saveWifiConfig(new_config);
                    this->enterOperational();
                }
                else
                {
                    wifi_.disconnect(true);
                    this->networkConfigurationPortal();
                }
            }
            break;
        }
        case State::ConnectingWifi: {
            Serial.println("Is connectinfWifi");
            if (wifi_.waitForConnection(10000)) {
                Serial.println("Wifi connection established");
                enterOperational();
            }else {
                Serial.print("Fail to connect to wifi: SSID ");
                Serial.println(config_.wifiConfig.ssid);
                wifi_.disconnect(true);
                //TODO colocar função que apaga da memória também
                config_.wifiConfig.clear();
                this->networkConfigurationPortal();
            }
            break;
        }
        case State::Operational: {
            Serial.println("Is operational");
            webServer_.tick();
            if (webServer_.hasResetWifiRequest()) {
                Serial.println("Reset WiFi consumido pelo Kernel");
                webServer_.consumeResetWifiRequest();

                memoryConfigRepository_.clearWifiConfig();
                config_.wifiConfig.clear();

                wifi_.disconnect(true);

                this->networkConfigurationPortal();
            }

            break;
        }
    default: break;
    }
}

void Kernel::loadNetworkingConfiguration() {
    config_.wifiConfig = memoryConfigRepository_.loadWifiConfig();
}

void Kernel::networkConfigurationPortal() {
    state_ = State::ConfigPortal;
    networkingService_.start();
}

void Kernel::enterWifi() {
    state_ = State::ConnectingWifi;
    wifi_.startStation(config_.wifiConfig.ssid, config_.wifiConfig.psw);
}

void Kernel::enterOperational() {
    state_ = State::Operational;
    webServer_.beginDashboard();
    Serial.println(wifi_.localIP());
}
