#include <config.h>
#include <display.h>
#include <gradient.h>

CRGB _from;
double _rr, _rg, _rb;
double steps = 9;

void Gradient::Initialize(CRGB from, CRGB to) {
    _from = from;
    _rr = (to.r - from.r) / steps;
    _rg = (to.g - from.g) / steps;
    _rb = (to.b - from.b) / steps;
}

// TODO: implement horizontal/vertical (angle?) gradient
// TODO: implement scroll?
// TODO: implement gradients with more than 2 colors?

void Gradient::Handle(Time time) {
    for (uint8_t x = 0; x < Display::GetCols(); x++) {
        for (uint8_t y = 0; y < Display::GetRows(); y++) {
            Display::SetLED(x, y, CRGB(_from.r + (y * _rr), _from.g + (y * _rg), _from.b + (y * _rb)));
        }
    }
}