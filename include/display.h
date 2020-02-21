#ifndef DISPLAY_H
#define DISPLAY_H

#include <FastLED.h>

class Display
{
public:
    static void Initialize();
    static void SetLED(int index, CRGB color);
    static void Refresh();
private:
    static void Clear();
    static double GetBlinkValue(long time, double freq = .5, int min = 0, int max = 255);
    static double Mapf(double x, double in_min, double in_max, double out_min, double out_max);
};
#endif