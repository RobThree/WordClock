#include <Arduino.h>
#include <display.h>
#include <config.h>
#include <statusbar.h>

CRGB leds[DISPLAY_NUM_LEDS_TOTAL];
uint32_t nextldrreading = 0;
uint32_t lastldrreading = 0;
uint8_t targetbrightness = LDR_LIGHT;
uint8_t lastbrightness = 0;

void Display::Initialize() {
    FastLED.addLeds<DISPLAY_LED_TYPE, DISPLAY_LED_PIN, DISPLAY_COLOR_ORDER>(leds, DISPLAY_NUM_LEDS_TOTAL).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(LDR_DARK);
    Clear();
    Refresh();
}

uint8_t Display::GetRows() { return DISPLAY_ROWS; }
uint8_t Display::GetCols() { return DISPLAY_COLS; }
uint8_t Display::GetTotalScreenLeds() { return DISPLAY_NUM_LEDS_SCREEN; }

CRGB Display::GetLED(uint8_t index) {
    if (CheckBounds(index))
        return leds[MapLED(index)];
    return CRGB::Black;
}

CRGB Display::GetLED(uint8_t row, uint8_t col) {
    return GetLED((row * DISPLAY_COLS) + col);
}

void Display::SetLED(uint8_t index, CRGB color) {
    if (CheckBounds(index))
        leds[MapLED(index)] = color;
}

void Display::SetLED(uint8_t row, uint8_t col, CRGB color) {
    SetLED((row * DISPLAY_COLS) + col, color);
}

uint8_t Display::MapLED(uint8_t index) {
    uint8_t row = index / DISPLAY_COLS;
    return (row % 2 == 0)	// If uneven row, numbering is from right to left
        ? ((row + 1) * DISPLAY_COLS) - (index % DISPLAY_COLS) + DISPLAY_NUM_STATUSLEDS - 1
        : index + DISPLAY_NUM_STATUSLEDS;
}

bool Display::CheckBounds(uint8_t index) {
    return (index >= 0 && index < DISPLAY_NUM_LEDS_SCREEN);
}

void Display::Clear() {
    for (uint8_t i = 0; i < DISPLAY_NUM_LEDS_SCREEN; i++)
        SetLED(i, CRGB::Black);
}

void Display::Refresh() {
    uint32_t time = millis();

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
double Display::GetBlinkValue(uint32_t time, double freq, uint8_t min, uint8_t max)
{
    // Scale a second to 256 'ticks'/sec and multiply by frequency, calculate the
    // quadwave8 (fast sin approximation provided by FastLED library) and finally
    // map to our desired range.
    return map(quadwave8(time * 0.256 * freq), 0, 255, min, max);   
}