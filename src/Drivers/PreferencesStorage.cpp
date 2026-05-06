#include "PreferencesStorage.h"

namespace Drivers {

    auto PreferencesStorage::begin(const char* namespaceName, bool readOnly) -> bool
    {
        return preferences_.begin(namespaceName, readOnly);
    }

    void PreferencesStorage::end()
    {
        preferences_.end();
    }
}