#include <Arduino.h>
#include <ntpclock.h>
#include <config.h>

static Timezone tz;

void NTPClock::Initialize() {
    Serial.printf("Initializing NTP (server: %s, interval: %ds, timezone: %s)\n", NTP_SERVER, NTP_SYNCINTERVAL, NTP_TIMEZONE);
    setServer(NTP_SERVER);
    setInterval(NTP_SYNCINTERVAL);
    waitForSync();
    tz.setLocation(F(NTP_TIMEZONE));
    Serial.printf("NTP initialized\n");
}

long NTPClock::Now() {
    events();
    return tz.now();
}