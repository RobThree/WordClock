#include <Arduino.h>
#include <stdarg.h>
#include <wifi.h>
#include <ntpclock.h>
#include <clock.h>
#include <display.h>
#include <statusbar.h>
#include <ota.h>
#include <config.h>

long frameduration;

void setup()
{
    Serial.begin(460800);
    Serial.println("Wait for it...");
    Serial.println("Booting...");

    // Calculate frame duration (in milliseconds) once, so we don't need to keep doing this
    frameduration = 1000 / CLOCK_FPS;

    StatusBar::Initialize();
    Display::Initialize();
    WIFI::Initialize();
    NTPClock::Initialize();
    OTA::Initialize();
}

void loop()
{
    // Get current time
    long time = millis();

    // Main loop
    OTA::Handle();
    Clock::TimestampToDisplay(NTPClock::Now(), CLOCK_USEROUNDING);
    WIFI::UpdateStatus();
    Display::Refresh();
    
    // Determine at what time the next frame should be ready and how long we should
    // wait and then delay for that time.
    long t_next = time + frameduration;
    long t_wait = t_next - millis();
    delay(t_wait >= 0 ? t_wait : 0);
}