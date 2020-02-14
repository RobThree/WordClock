#include <Arduino.h>
#include <stdarg.h>
#include <wifi.h>
#include <ntpclock.h>
#include <clock.h>
#include <display.h>
#include <statusbar.h>

void setup()
{
    Serial.begin(460800);
    Serial.println("Wait for it...");

    delay(3000);    // Power-up safety delay
    
    Serial.println("Booting...");
    
    StatusBar::Initialize();
    Display::Initialize();
    WIFI::Initialize();
    NTPClock::Initialize();
}

void loop()
{
    Clock::TimestampToDisplay(NTPClock::Now(), true);
    Display::Refresh();
    delay(100);
}