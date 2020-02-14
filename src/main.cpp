#include <Arduino.h>
#include <stdarg.h>
#include <wifi.h>
#include <ntpclock.h>
#include <clock.h>
#include <display.h>

void setup()
{
    Serial.begin(460800);
    Serial.println("Starting...");

    WIFI::Initialize();
    NTPClock::Initialize();
    
    Display::Initialize();
}

void loop()
{
    Display::Clear();

    Clock::TimestampToDisplay(NTPClock::Now(), true);

    delay(1000);
}