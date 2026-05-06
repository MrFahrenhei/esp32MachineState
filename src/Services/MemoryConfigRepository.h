#pragma once
#include "Config/WifiConfig.h"
#include "Drivers/PreferencesStorage.h"
namespace Services {
class MemoryConfigRepository {
   public:
    explicit MemoryConfigRepository(Drivers::PreferencesStorage& storage);
    void saveWifiConfig(Config::WifiConfig& config);
    auto loadWifiConfig() const -> Config::WifiConfig;
    void clearWifiConfig();
   private:
    Drivers::PreferencesStorage& storage_;
};
}  // namespace Services