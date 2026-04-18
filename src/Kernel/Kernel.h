#pragma once
#include "State.h"
#include <Arduino.h>
#include "../Services/NetworkingService.h"
#include "../Drivers/WifiDriver.h"

#include "Config/Config.h"
#include "Drivers/WebServerDriver.h"

class Kernel {
public:
    Kernel();
    void boot();
    void tick();
private:
    void loadNetworkingConfiguration();
    void networkConfigurationPortal();
    void enterWifi();
    void enterOperational();
private:
    Config::Config _config;
    State _state = State::Booting;

    Drivers::WifiDriver _wifi;
    Drivers::WebServerDriver _webServer;

    Services::NetworkingService _networkingService;
};
