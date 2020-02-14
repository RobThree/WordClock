#include <Arduino.h>
#include <ntpclock.h>
#include <config.h>
#include <statusbar.h>
#include <display.h>

static Timezone tz;

void NTPClock::Initialize() {
    Serial.printf("Initializing NTP (server: %s, interval: %ds, timezone: %s)\n", NTP_SERVER, NTP_SYNCINTERVAL, NTP_TIMEZONE);
    StatusBar::SetClockStatus(StatusBar::CLOCK_STATUS::CS_SYNCING);
    Display::Refresh();
    setServer(NTP_SERVER);
    setInterval(NTP_SYNCINTERVAL);
    waitForSync();
    tz.setLocation(F(NTP_TIMEZONE));
    Serial.printf("NTP initialized\n");
    StatusBar::SetClockStatus(StatusBar::CLOCK_STATUS::CS_SYNCED);
    Display::Refresh();
}

long NTPClock::Now() {
    events();
    return tz.now();
}