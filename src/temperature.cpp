#include <config.h>
#include <display.h>
#include <temperature.h>
#include <Arduino.h>

    //   0      |   1      |   2      |   3      |   4      |   5      |   6      |   7      |   8      |   9      |   °      |   f      |   -      |  Space  | 
    //   111  7 |   001  1 |   111  7 |   111  7 |   101  5 |   111  7 |   111  7 |   111  7 |   111  7 |   111  7 |   111  7 |   111  7 |   000  0 |  000  0 | 
    //   101  5 |   111  3 |   001  1 |   001  1 |   101  5 |   100  4 |   100  4 |   001  1 |   101  5 |   101  5 |   101  5 |   100  4 |   000  0 |  000  0 | 
    //   101  5 |   001  1 |   001  1 |   001  1 |   101  5 |   100  4 |   100  4 |   001  1 |   101  5 |   101  5 |   111  7 |   111  7 |   000  0 |  000  0 | 
    //   101  5 |   001  1 |   111  7 |   111  7 |   111  7 |   111  7 |   111  7 |   010  2 |   111  7 |   111  7 |   000  0 |   100  4 |   111  7 |  000  0 | 
    //   101  5 |   001  1 |   100  4 |   001  1 |   001  1 |   001  1 |   101  5 |   010  2 |   101  5 |   001  1 |   000  0 |   000  0 |   000  0 |  000  0 | 
    //   101  5 |   001  1 |   100  4 |   001  1 |   001  1 |   001  1 |   101  5 |   010  2 |   101  5 |   001  1 |   000  0 |   000  0 |   000  0 |  000  0 | 
    //   111  7 |   001  1 |   111  7 |   111  7 |   001  1 |   111  7 |   111  7 |   010  2 |   111  7 |   111  7 |   000  0 |   000  0 |   000  0 |  000  0 | 

uint8_t _fontheight = 7;
uint8_t _fontwidth = 3;

uint8_t _font[] = {
    /* 0 */ 7, 5, 5, 5, 5, 5, 7,
    /* 1 */ 1, 7, 1, 1, 1, 1, 1,
    /* 2 */ 7, 1, 1, 7, 4, 4, 7,
    /* 3 */ 7, 1, 1, 7, 1, 1, 7,
    /* 4 */ 5, 5, 5, 7, 1, 1, 1,
    /* 5 */ 7, 4, 4, 7, 1, 1, 7,
    /* 6 */ 7, 4, 4, 7, 5, 5, 7,
    /* 7 */ 7, 1, 1, 2, 2, 2, 2,
    /* 8 */ 7, 5, 5, 7, 5, 5, 7,
    /* 9 */ 7, 5, 5, 7, 1, 1, 7,
    /* ° */ 7, 5, 7, 0, 0, 0, 0,
    /* f */ 7, 4, 7, 4, 0, 0, 0,
    /* - */ 0, 0, 0, 7, 0, 0, 0,
    /*   */ 0, 0, 0, 0, 0, 0, 0,
};

const uint8_t CELSIUS = 10;
const uint8_t FAHRENHEIT = 11;
const uint8_t MINUS = 12;
const uint8_t SPACE = 13;

CRGB _coldcolor, _warmcolor;
uint8_t _xoff, _yoff;

void Temperature::Initialize(uint8_t x_offset, uint8_t y_offset, CRGB coldcolor, CRGB warmcolor) {
    _xoff = x_offset;
    _yoff = y_offset;
    _coldcolor = coldcolor;
    _warmcolor = warmcolor;
}

void Temperature::Handle(Time time) {
    uint64_t buffer[_fontheight];

    for (int i=0;i<_fontheight;i++)
        buffer[i] = 0;

    // TODO: Read actual temp sensor - create/use an interface (like ITempSensor) that is initialized in the Initialize() method
    // so we can use different sensors like DHT11, DHT22, DS18B20 etc.
    int temperature = (time.time % 40) - 20;

    // Determine digits
    uint8_t tens = abs(temperature / 10);
    AddSymbol(buffer, tens == 0 ? (temperature < 0 ? MINUS : SPACE) : tens);    // Display then tens; if it is a 0 then display a minus
                                                                                // in it's place for negative temps, else a space
    AddSymbol(buffer, abs(temperature % 10));                                   // Display the ones
    AddSymbol(buffer, TEMPERATURE_UNIT);                                        // ° or f

    ToDisplay(buffer, temperature <= 0 ? _coldcolor : _warmcolor);
}

void Temperature::ToDisplay(uint64_t buffer[], CRGB color) {
    uint8_t cols = Display::GetCols() - 1;
    for (int y = 0; y < _fontheight; y++) {
        for (int x = 0; x <= cols; x++) {
            if ((buffer[y] >> x) & 1)
                Display::SetLED(_xoff + cols - x, _yoff + y, color);
        }
    }
}

void Temperature::AddSymbol(uint64_t buffer[], uint8_t symbol) {
    for (uint8_t i = 0; i < _fontheight; i++)
        buffer[i] = (buffer[i] << (_fontwidth + 1)) | _font[(symbol * _fontheight) + i];
}