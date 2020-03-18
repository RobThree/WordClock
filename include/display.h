#ifndef DISPLAY_H
#define DISPLAY_H

#include <FastLED.h>

class Display
{
public:
    static void Initialize();
    static void SetLED(uint8_t index, CRGB color);
    static void SetLED(uint8_t row, uint8_t col, CRGB color);
    static CRGB GetLED(uint8_t index);
    static CRGB GetLED(uint8_t row, uint8_t col);
    static void Refresh();
private:
    static void Clear();
    static double GetBlinkValue(uint32_t time, double freq = .5, uint8_t min = 0, uint8_t max = 255);
    static uint8_t MapLED(uint8_t index);
    static bool CheckBounds(uint8_t index);
};
#endif