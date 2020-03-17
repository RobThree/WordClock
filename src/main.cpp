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
    Serial.begin(460800);
    Serial.println("Booting...");

    pinMode(DISPLAY_LED_PIN, OUTPUT);
    pinMode(LDR_PIN, INPUT);
    
    // Calculate frame duration (in milliseconds) once, so we don't need to keep doing this
    frameduration = 1000 / CLOCK_FPS;

    StatusBar::Initialize();
    Display::Initialize();
    WIFI::Initialize();
    NTPClock::Initialize();
    OTA::Initialize();

    // Example animations
    // Animation::SetAnimation("http://xs4any.nl/marios/spiral.bin");
    // Animation::SetAnimation("http://xs4any.nl/marios/testscreen.bin");
    // Animation::SetAnimation("http://xs4any.nl/marios/mario.bin");
    // Animation::SetAnimation("http://xs4any.nl/marios/hearts.bin");
    // Animation::SetAnimation("http://xs4any.nl/marios/fireworks.bin");
    // Animation::SetAnimation("http://xs4any.nl/marios/matrix.bin");
}

void loop()
{
    // Get current time
    long time = millis();

    // Main loop
    OTA::Handle();

    // comment Clock::TimestampToDisplay(...) and uncomment next line to switch to animation-mode
    // of course this needs some sort of state switching, but for now this is it
    // a fun party trick is to leave them on both, I recommend matrix.bin for this
    // Animation::SetAnimationFrame(time);

    Clock::TimestampToDisplay(NTPClock::Now(), CLOCK_USEROUNDING);
    
    Display::Refresh();
    
    // Determine at what time the next frame should be ready and how long we should
    // wait and then delay for that time.
    long t_next = time + frameduration;
    long t_wait = t_next - millis();
    delay(t_wait >= 0 ? t_wait : 0);
}