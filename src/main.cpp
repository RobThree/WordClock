#include <Arduino.h>
#include <stdarg.h>
#include <wifi.h>
#include <clock.h>

void setup()
{
    Serial.begin(460800);
    Serial.println("Starting...");

    InitWiFi();
}

long timestamp = 1566934404; // Tuesday, August 27, 2019 7:33:24 PM UTC

void loop()
{
    // put your main code here, to run repeatedly:

    ClearLeds();

    Serial.print(timestamp);
    Serial.print(": ");
    TimestampToLEDS(timestamp, true);
    Serial.println();
    timestamp += random(86400); // Add random 0 - 24h period
    delay(1000);
}