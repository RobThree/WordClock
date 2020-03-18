#ifndef DISPLAY_H
#define DISPLAY_H

#include <FastLED.h>

class Display
{
public:
    static void Initialize();
    static void SetLED(uint8_t index, CRGB color);
    static void SetLED(uint8_t col, uint8_t row, CRGB color);
    static CRGB GetLED(uint8_t index);
    static CRGB GetLED(uint8_t col, uint8_t row);
    static uint8_t GetRows();
    static uint8_t GetCols();
    static uint8_t GetTotalScreenLeds();
    static void Refresh();
    static void Clear();
    static void Fill(CRGB color);
private:
    static double GetBlinkValue(uint32_t time, double freq = .5, uint8_t min = 0, uint8_t max = 255);
    static uint8_t MapLED(uint8_t index);
    static bool CheckBounds(uint8_t index);
};
#endif