//
// Created by beraldo on 17/04/2026.
//

#include "WebServerDriver.h"

namespace Drivers {
    WebServerDriver::WebServerDriver(): _server(80) {}

    void WebServerDriver::tick() {
        _server.handleClient();
    }
}
