#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <ihandler.h>

class Temperature : public IHandler
{
public:
    static void Initialize(uint8_t x_offset, uint8_t y_offset, CRGB coldcolor, CRGB warmcolor);
    static void Handle(Time time);
private:
    static void AddSymbol(uint64_t buffer[], uint8_t symbol);
    static void ToDisplay(uint64_t buffer[], CRGB color);
};
#endif