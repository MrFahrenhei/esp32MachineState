#pragma once
#include <Arduino.h>
#include "State.h"
#include "Config/Config.h"
#include "Drivers/WifiDriver.h"
#include "Drivers/WebServerDriver.h"
#include "Drivers/PreferencesStorage.h"
#include "Services/NetworkingService.h"
#include "Services/MemoryConfigRepository.h"

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

    Config::Config config_;
    State state_ = State::Booting;

    Drivers::WifiDriver wifi_;
    Drivers::WebServerDriver webServer_;
    Drivers::PreferencesStorage preferencesStorage_;

    Services::MemoryConfigRepository memoryConfigRepository_;
    Services::NetworkingService networkingService_;
};
