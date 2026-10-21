#include <Arduino.h>
#include "printer.h"

namespace {
constexpr int TX_GPIO = 3;
constexpr int RX_GPIO = 2;
}

void initPrinter() {
    Serial1.begin(9600, SERIAL_8N1, RX_GPIO, TX_GPIO);
    delay(500);
    Serial1.write(0x1B);
    Serial1.write('@');
}

void align(Alignment a) {
    Serial1.write(0x1B);
    Serial1.write('a');
    Serial1.write(static_cast<uint8_t>(a));
}

void writeText(const String& text) {
    Serial1.print(text);
}

void newLine() {
    Serial1.print("\r\n");
}

void feedLines(uint8_t lines) {
    Serial1.write(0x1B);
    Serial1.write('d');
    Serial1.write(lines);
}

void cut() {
    Serial1.write(0x1D);
    Serial1.write('V');
    Serial1.write(1);  // Partial cut
    Serial1.flush();
}
