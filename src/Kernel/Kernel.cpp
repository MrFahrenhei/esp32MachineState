#include "Kernel.h"

Kernel::Kernel(): _networkingService(_wifi, _webServer) {
    Serial.println("Construct do kernel");
}

void Kernel::boot() {
    Serial.println("Boot do kernel");
    this->loadNetworkingConfiguration();
    if (_config.wifiConfig.configured == false) {
        Serial.println("Não está configurado Wifi");
        this->networkConfigurationPortal();
    }else {
        Serial.print("Está configurado no wifi: ");
        Serial.println(_config.wifiConfig.ssid);
        this->enterWifi();
    }
}

void Kernel::tick() {
    switch (_state) {
        case State::ConfigPortal: {
            Serial.println("Is configPortal");
            if (_webServer._hasPendingConfig) {
                _wifi.disconnect(false);
                _wifi.startStation()
            }
            break;
        }
        case State::ConnectingWifi: {
            Serial.println("Is connectinfWifi");
            if (_wifi.waitForConnection(10000)) {
                Serial.println("Wifi connection established");
                enterOperational();
            }else {
                Serial.print("Fail to connect to wifi: SSID ");
                Serial.println(_config.wifiConfig.ssid);
                _wifi.disconnect(true);
                //TODO colocar função que apaga da memória também
                _config.wifiConfig.clear();
                this->networkConfigurationPortal();
            }
            break;
        }
        case State::Operational: {
            Serial.println("Is operational");
            break;
        }
    }
}

void Kernel::loadNetworkingConfiguration() {
    Config::WifiConfig mockupConfig{};
#ifdef FAKER
    mockupConfig.configured = true;
    strcpy(mockupConfig.ssid, "Avetools-Impressora");
    strcpy(mockupConfig.psw, "824l@@DL3n*");
#endif
    this->_config.wifiConfig = mockupConfig;
}

void Kernel::networkConfigurationPortal() {
    _state = State::ConfigPortal;
    _networkingService.start();
}

void Kernel::enterWifi() {
    _state = State::ConnectingWifi;
    _wifi.startStation(_config.wifiConfig.ssid, _config.wifiConfig.psw);
}

void Kernel::enterOperational() {
    _state = State::Operational;
}
