#pragma once
#include <WebServer.h>
namespace Drivers {
    class WebServerDriver {
    public:
        WebServerDriver();
        void tick();
        uint8_t _hasPendingConfig = false;
    private:
        WebServer _server;
    };
}


