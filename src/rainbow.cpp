#include <config.h>
#include <display.h>
#include <rainbow.h>

uint8_t _brightness;
uint8_t _speed;

void Rainbow::Initialize(uint8_t brightness, uint8_t speed) {
    _brightness = brightness;
    _speed = speed;
}

// TODO: implement horizontal/vertical (angle?) rainbow
// TODO: implement direction for scroll

void Rainbow::Handle(HandlerInfo info) {
    uint8_t step = 256 / Display::GetCols();
    uint8_t offset = _speed != 0 ? (info.uptime / _speed) : 0;
    for (uint8_t x = 0; x < Display::GetCols(); x++) {
        for (uint8_t y = 0; y < Display::GetRows(); y++) {
            Display::SetLED(x, y, CHSV(((x * step) + offset) % 255, 255, _brightness));
        }
    }
}