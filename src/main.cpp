#include <Arduino.h>
#include <stdarg.h>
#include <wifi.h>
#include <ntpclock.h>
#include <clock.h>
#include <display.h>
#include <statusbar.h>
#include <ota.h>
#include <config.h>

void setup()
{
    Serial.begin(460800);
    Serial.println("Wait for it...");
    Serial.println("Booting...");

    StatusBar::Initialize();
    Display::Initialize();
    WIFI::Initialize();
    NTPClock::Initialize();
    OTA::Initialize();
}

void loop()
{
    OTA::Handle();
    Clock::TimestampToDisplay(NTPClock::Now(), CLOCK_USEOFFSET);
    WIFI::UpdateStatus();
    Display::Refresh();
    delay(100);
}