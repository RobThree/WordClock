#include <Arduino.h>
#include <stdarg.h>
#include <wifi.h>
#include <ntpclock.h>
#include <clock.h>
#include <display.h>
#include <statusbar.h>
#include <ota.h>
#include <config.h>
#include <animation.h>
#include <solidcolor.h>
#include <rainbow.h>
#include <gradient.h>
#include <temperature.h>

uint16_t _frameduration;
Time _time;
uint8_t _effect = 0;

void seteffect(uint8_t effect)
{
    _effect = effect % 9;
    Serial.printf("Initializing effect %d\n", _effect);
    switch (_effect)
    {
        case 1:
            SolidColor::Initialize(CRGB(40,10,0));
            break;
        case 2:
            Rainbow::Initialize(128, 25);
            break;
        case 3:
            Gradient::Initialize(CRGB(255, 0, 0), CRGB(0, 255, 0));
            break;
        case 4:
            Animation::Initialize("/fire.bin");
            break;
        case 5:
            Animation::Initialize("/spiral.bin");
            break;
        case 6:
            Animation::Initialize("/mario.bin");
            break;
        case 7:
            Animation::Initialize("/fireworks.bin");
            break;
        case 8:
            Animation::Initialize("/matrix.bin");
            break;
        default:
            SolidColor::Initialize(CRGB(0,0,0));
            break;
    }
}

void handleeffect(uint8_t effect) {
    switch (effect)
    {
        case 0:
            break;
        case 1:
            SolidColor::Handle(_time);
            break;
        case 2:
            Rainbow::Handle(_time);
            break;
        case 3:
            Gradient::Handle(_time);
            break;
        default:
            Animation::Handle(_time);
            break;
    }
}

void setup()
{
    Serial.begin(SERIAL_SPEED);
    Serial.println("Booting");

    pinMode(DISPLAY_LED_PIN, OUTPUT);
    pinMode(LDR_PIN, INPUT);
    pinMode(BUTTON_EFFECTS, INPUT_PULLUP);

    // Calculate frame duration (in milliseconds) once
    _frameduration = 1000 / CLOCK_FPS;

    StatusBar::Initialize();
    Display::Initialize();
    WIFI::Initialize();
    Clock::Initialize();
    NTPClock::Initialize();
    OTA::Initialize();
    // Temperature::Initialize(TEMPERATURE_XOFF, TEMPERATURE_YOFF, TEMPERATURE_COLD_COLOR, TEMPERATURE_WARM_COLOR);

    seteffect(_effect);
    // StatusBar::Disable();
}

void loop()
{
    OTA::Handle();

    // Split time parts of last time into low/high DWORDS
    uint32_t time_l = _time.uptime >> 32;
    uint32_t time_h = _time.uptime;
    // Get current time
    uint32_t ctime = millis();

    // Handle rollover/overflow
    if (ctime < time_h)
        time_l++;   // Increase low DWORD

    // Reassemble time
    _time.uptime = ((uint64_t)time_l << 32) | ctime;
    // Store current time in seconds since epoch
    _time.time = NTPClock::Now();

    // Change effect?
    if (digitalRead(D6) == 0) {
        seteffect(++_effect);
        delay(300);
    }

    // Effect
    handleeffect(_effect);    

    // Actual time
    Clock::Handle(_time);
    // Temperature::Handle(_time);
    
    Display::Refresh(_time);

    // Determine at what time the next frame should be ready and how long we should
    // wait and then delay for that time. Note that we're working in the 32bit domain
    // here. We're calling millis() here again because we want to take into account
    // the actual duration of the time the last frame took since last time we called
    // millis() at the top of this function.
    uint32_t t_wait = (ctime + _frameduration) - millis();
    delay(t_wait <= _frameduration ? t_wait : 0);
}