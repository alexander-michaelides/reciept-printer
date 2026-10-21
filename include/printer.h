#pragma once
#include <Arduino.h>

enum class Alignment {
    Center = 1,
    Left = 0,
    Right = 2,
};

void initPrinter();
void align(Alignment a);
void writeText(const String& text);
void newLine();
void feedLines(uint8_t lines);
void cut();
