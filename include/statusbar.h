#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <FastLED.h>

class StatusBar {
    public:
        enum CLOCK_STATUS {
            CS_NONE = CRGB::Black,
            CS_SYNCING = CRGB::Yellow,
            CS_SYNCED = CRGB::Green
        };

        enum PARTY_STATUS {
            PS_NONE = CRGB::Black,
            PS_BIRTHDAY = CRGB::Yellow,
            PS_HOLIDAY = CRGB::Green
        };

        enum ALARM_STATUS {
            AS_NONE = CRGB::Black,
            AS_ARMED = CRGB::White
        };

        enum WIFI_STATUS {
            WS_NONE = CRGB::Black,
            WS_DISCONNECTED = CRGB::Red,
            WS_CONNECTING = CRGB::Yellow,
            WS_CONNECTED = CRGB::Green,

            WS_OTASTART = CRGB::Pink,
            WS_OTAPROGRESS1 = CRGB::Blue,
            WS_OTAPROGRESS2 = CRGB::LightBlue,
            WS_OTACOMPLETE = CRGB::White,
            WS_OTAERROR = CRGB::DarkRed
        };

        static void Initialize();
        static void SetClockStatus(StatusBar::CLOCK_STATUS status);
        static CLOCK_STATUS GetClockStatus();
        static void SetPartyStatus(PARTY_STATUS status);
        static PARTY_STATUS GetPartyStatus();
        static void SetAlarmStatus(ALARM_STATUS status);
        static ALARM_STATUS GetAlarmStatus();
        static void SetWiFiStatus(WIFI_STATUS status);
        static WIFI_STATUS GetWiFiStatus();
};
#endif