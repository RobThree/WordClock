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

uint32_t frameduration;

void setup()
{
    Serial.begin(SERIAL_SPEED);
    Serial.println("Booting...");

    pinMode(DISPLAY_LED_PIN, OUTPUT);
    pinMode(LDR_PIN, INPUT);
    
    // Calculate frame duration (in milliseconds) once, so we don't need to keep doing this
    frameduration = 1000 / CLOCK_FPS;

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
    // Get current time
    Time time;
    time.uptime = millis();
    time.time = NTPClock::Now();

    // Main loop
    OTA::Handle();

    // Effects:
    // Animation::Handle(time);
    // SolidColor::Handle(time);
    // Rainbow::Handle(time);
    // Gradient::Handle(time);
    
    // Actual time
    Clock::Handle(time);
    
    Display::Refresh(time);

    // Determine at what time the next frame should be ready and how long we should
    // wait and then delay for that time.
    uint32_t t_next = time.uptime + frameduration;
    uint32_t t_wait = t_next - millis();
    delay(t_wait <= frameduration ? t_wait : 0);
}