#include <Arduino.h>
#include <stdarg.h>
#include <wifi.h>
#include <ntpclock.h>
#include <clock.h>

void setup()
{
    Serial.begin(460800);
    Serial.println("Starting...");

    WIFI::Initialize();
    NTPClock::Initialize();
}

void loop()
{
    Clock::ClearLeds();

    Clock::TimestampToLEDS(NTPClock::Now(), true);
    Serial.println();
    delay(1000);
}