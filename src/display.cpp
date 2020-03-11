#include <Arduino.h>
#include <display.h>
#include <config.h>
#include <statusbar.h>

CRGB leds[DISPLAY_NUM_LEDS];
long nextldrreading = 0;
long lastldrreading = 0;
uint8_t targetbrightness = LDR_LIGHT;
uint8_t lastbrightness = 0;

void Display::Initialize() {
    FastLED.addLeds<DISPLAY_LED_TYPE, DISPLAY_LED_PIN, DISPLAY_COLOR_ORDER>(leds, DISPLAY_NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(LDR_DARK);
    Clear();
    Refresh();
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
    long time = millis();

    if (time >= nextldrreading) {
        lastldrreading = time;
        nextldrreading = lastldrreading + LDR_FADE_TIME;
        lastbrightness = FastLED.getBrightness();
        targetbrightness = map(analogRead(LDR_PIN), 0, 1024, LDR_DARK, LDR_LIGHT);
    }

    FastLED.setBrightness(map(time, lastldrreading, nextldrreading, lastbrightness, targetbrightness));

    leds[STATUSLED_CLOCK] = StatusBar::GetClockStatus();
    leds[STATUSLED_HEART] = CHSV(0, 255, GetBlinkValue(time));
    leds[STATUSLED_PARTY] = StatusBar::GetPartyStatus();
    leds[STATUSLED_ALARM] = StatusBar::GetAlarmStatus();
    leds[STATUSLED_WIFI]  = StatusBar::GetWiFiStatus();
    
    FastLED.show();
    Clear();
}

// Returns a brightness for a given point in time and frequency so that blinks stay
// in sync (as much as possible) with actual time.
double Display::GetBlinkValue(long time, double freq, int min, int max)
{
    // Scale a second to 256 'ticks'/sec and multiply by frequency, calculate the
    // quadwave8 (fast sin approximation provided by FastLED library) and finally
    // map to our desired range.
    return map(quadwave8(time * 0.256 * freq), 0, 255, min, max);   
}