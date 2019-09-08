#include <Arduino.h>
#include <ntpclock.h>
#include <config.h>

static Timezone tz;

void NTPClock::Initialize() {
    Serial.println("Initializing NTP");
    setServer(NTP_SERVER);
    setInterval(NTP_SYNCINTERVAL);
    waitForSync();
    tz.setLocation(F(NTP_TIMEZONE));
    Serial.println("NTP initialized");
}

long NTPClock::Now() {
    events();
    return tz.now();
}