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

long frameduration;

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

    // Example animations
    // Animation::Initialize("http://xs4any.nl/marios/spiral.bin");
    // Animation::Initialize("http://xs4any.nl/marios/testscreen.bin");
    // Animation::Initialize("http://xs4any.nl/marios/mario.bin");
    // Animation::Initialize("http://xs4any.nl/marios/hearts.bin");
    // Animation::Initialize("http://xs4any.nl/marios/fireworks.bin");
    // Animation::Initialize("http://xs4any.nl/marios/matrix.bin");
}

void loop()
{
    // Get current time
    HandlerInfo info;
    info.uptime = millis();
    info.time = NTPClock::Now();

    // Main loop
    OTA::Handle();

    // Comment Clock::TimestampToDisplay(...) and uncomment next line to switch to animation-mode
    // Ofcourse this needs some sort of state switching, but for now this is it
    // a fun party trick is to leave them on both, I recommend matrix.bin for this
    // Animation::Handle(info);
    Clock::Handle(info);
    
    Display::Refresh();
    
    // Determine at what time the next frame should be ready and how long we should
    // wait and then delay for that time.
    uint32_t t_next = info.uptime + frameduration;
    uint32_t t_wait = t_next - millis();
    delay(t_wait >= 0 ? t_wait : 0);
}