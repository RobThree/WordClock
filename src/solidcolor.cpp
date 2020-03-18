#include <config.h>
#include <display.h>
#include <solidcolor.h>

CRGB _color;
void SolidColor::Initialize(CRGB color) {
    _color = color;
}

void SolidColor::Handle(HandlerInfo info) {
    Display::Fill(_color);
}