#pragma once
#include <Preferences.h>
namespace Drivers {
class PreferencesStorage {
public:
    auto begin(const char* namespaceName, bool readOnly = false) -> bool;
    void end();

    template <typename T>
    auto putObject(const char* key, const T& value) -> bool
    {
        size_t written = preferences_.putBytes(key, &value, sizeof(T));
        return written == sizeof(T);
    }

    template<typename T>
    auto getObject(const char* key, T& value) -> bool {
        size_t expectedSize = sizeof(T);
        size_t storedSize = preferences_.getBytesLength(key);
        if (storedSize != expectedSize) {
            return false;
        }
        size_t read = preferences_.getBytes(key, &value, expectedSize);
        return read == expectedSize;
    }
private:
    Preferences preferences_;
};
}