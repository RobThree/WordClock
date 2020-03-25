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

uint16_t _frameduration;
Time _time;

void setup()
{
    Serial.begin(SERIAL_SPEED);
    Serial.println("Booting...");

    pinMode(DISPLAY_LED_PIN, OUTPUT);
    pinMode(LDR_PIN, INPUT);
    
    // Calculate frame duration (in milliseconds) once, so we don't need to keep doing this
    _frameduration = 1000 / CLOCK_FPS;

    StatusBar::Initialize();
    Display::Initialize();
    WIFI::Initialize();
    Clock::Initialize();
    NTPClock::Initialize();
    OTA::Initialize();
    
    // Effects:

    // SolidColor::Initialize(CRGB(40,10,0));
    // Rainbow::Initialize(128, 25);
    // Gradient::Initialize(CRGB(255, 0, 0), CRGB(0, 255, 0));
    
    // Example animations
    // Animation::Initialize("http://xs4any.nl/marios/fire.bin");
    // Animation::Initialize("http://xs4any.nl/marios/spiral.bin");
    // Animation::Initialize("http://xs4any.nl/marios/testscreen.bin");
    // Animation::Initialize("http://xs4any.nl/marios/mario.bin");
    // Animation::Initialize("http://xs4any.nl/marios/hearts.bin");
    // Animation::Initialize("http://xs4any.nl/marios/fireworks.bin");
    // Animation::Initialize("http://xs4any.nl/marios/matrix.bin");
    
    // StatusBar::Disable();
}

void loop()
{
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

    // Main loop
    OTA::Handle();

    // Effects:
    // Animation::Handle(time);
    // SolidColor::Handle(time);
    // Rainbow::Handle(time);
    // Gradient::Handle(time);
    
    // Actual time
    Clock::Handle(_time);
    
    Display::Refresh(_time);

    // Determine at what time the next frame should be ready and how long we should
    // wait and then delay for that time. Note that we're working in the 32bit domain
    // here. We're calling millis() here again because we want to take into account
    // the actual duration of the time the last frame took since last time we called
    // millis() at the top of this function.
    uint32_t t_wait = (ctime + _frameduration) - millis();
    delay(t_wait <= _frameduration ? t_wait : 0);
}