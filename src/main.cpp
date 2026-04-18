#include <Arduino.h>
#include "Kernel/Kernel.h"
Kernel kernel;
void setup() {
    Serial.begin(115200);
    delay(1000);
    kernel.boot();
}

void loop() {
    kernel.tick();
    delay(1000);
}