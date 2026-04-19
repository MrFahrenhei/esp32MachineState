#include <Arduino.h>
#include "Kernel/Kernel.h"
Kernel kernel;
void setup() {
    Serial.begin(115200);
    delay(2000);
    Serial.println("Fazendo boot");
    kernel.boot();
}

void loop() {
    kernel.tick();
    delay(1000);
}