#include <Arduino.h>
#include "wifi_handler.h"
#include "printer.h"

void setup() {
    Serial.begin(115200);
    initPrinter();
    initNetwork();
}

void loop() {
    handleNetwork();
}
