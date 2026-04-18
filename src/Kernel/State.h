#pragma once
#include <cstdio>
enum class State : uint8_t {
   Booting,
   ConfigPortal,
   ConnectingWifi,
   Operational,
};