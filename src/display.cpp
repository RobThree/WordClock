#include <Arduino.h>
#include <display.h>
#include <config.h>
#include <statusbar.h>

CRGB leds[DISPLAY_NUM_LEDS];

void Display::Initialize() {
    FastLED.addLeds<DISPLAY_LED_TYPE, DISPLAY_LED_PIN, DISPLAY_COLOR_ORDER>(leds, DISPLAY_NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(DISPLAY_BRIGHTNESS);
    Clear();
}

void Display::SetLED(int index, CRGB color) {
    if (index >= 0 && index < DISPLAY_NUM_LEDS)
        leds[index] = color;
}

void Display::Clear() {
    for (int i = 0; i < DISPLAY_NUM_LEDS; i++)
        SetLED(i, CRGB::Black);
}

void Display::Refresh() {
    leds[STATUSLED_CLOCK] = StatusBar::GetClockStatus();
    leds[STATUSLED_HEART] = StatusBar::GetHeartStatus();
    leds[STATUSLED_PARTY] = StatusBar::GetPartyStatus();
    leds[STATUSLED_ALARM] = StatusBar::GetAlarmStatus();
    leds[STATUSLED_WIFI]  = StatusBar::GetWiFiStatus();
    
    FastLED.show();
    Clear();
}