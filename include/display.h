#ifndef DISPLAY_H
#define DISPLAY_H

#include <FastLED.h>

class Display
{
public:
    static void Initialize();
    static void SetLED(int index, CRGB color);
    static void Clear();
};
#endif