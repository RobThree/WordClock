#include <Arduino.h>
#include <display.h>
#include <config.h>

CRGB leds[DISPLAY_NUM_LEDS];

void Display::Initialize() {
    FastLED.addLeds<DISPLAY_LED_TYPE, DISPLAY_LED_PIN, DISPLAY_COLOR_ORDER>(leds, DISPLAY_NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(DISPLAY_BRIGHTNESS);
}

void Display::SetLED(int index, CRGB color) {
    if (index >= 0 && index < DISPLAY_NUM_LEDS)
        leds[index] = color;
}

void Display::Clear() {
    for (int i = 0; i < DISPLAY_NUM_LEDS; i++)
        SetLED(i, CRGB::Black);
}