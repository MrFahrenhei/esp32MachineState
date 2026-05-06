#include "MemoryConfigRepository.h"

namespace Services {
MemoryConfigRepository::MemoryConfigRepository(Drivers::PreferencesStorage& storage): storage_(storage){}

void MemoryConfigRepository::saveWifiConfig(Config::WifiConfig& config) {
    Serial.println("Saving wifi into flash");
    if (!storage_.begin("device", false)) {
        return;
    }

    storage_.putObject("wifi_config",config);
    storage_.end();
}
auto MemoryConfigRepository::loadWifiConfig() const -> Config::WifiConfig {
    Serial.println("Retrieven wifi config from flash");
    Config::WifiConfig config{};
    if (!storage_.begin("device", true)) {
        return config;
    }

    storage_.getObject("wifi_config",config);
    storage_.end();
    return config;
}
void MemoryConfigRepository::clearWifiConfig()
{
    Serial.println("Clearing wifi from flash");
    Config::WifiConfig config{};
    config.clear();
    if (!storage_.begin("device", false)) {
        return;
    }
    storage_.putObject("wifi_config", config);
    storage_.end();
}
}