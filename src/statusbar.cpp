#include <statusbar.h>
#include <display.h>

StatusBar::CLOCK_STATUS clockstatus;
StatusBar::PARTY_STATUS partystatus;
StatusBar::ALARM_STATUS alarmstatus;
StatusBar::WIFI_STATUS  wifistatus;

bool _enabled = true;

void StatusBar::Initialize() {
    SetClockStatus(StatusBar::CLOCK_STATUS::CS_NONE);
    SetPartyStatus(StatusBar::PARTY_STATUS::PS_NONE);
    SetAlarmStatus(StatusBar::ALARM_STATUS::AS_NONE);
    SetWiFiStatus (StatusBar::WIFI_STATUS::WS_NONE);
}

void StatusBar::SetClockStatus(CLOCK_STATUS status) { clockstatus = status; }
StatusBar::CLOCK_STATUS StatusBar::GetClockStatus() { return clockstatus; }
void StatusBar::SetPartyStatus(PARTY_STATUS status) { partystatus = status; }
StatusBar::PARTY_STATUS StatusBar::GetPartyStatus() { return partystatus; }
void StatusBar::SetAlarmStatus(ALARM_STATUS status) { alarmstatus = status; }
StatusBar::ALARM_STATUS StatusBar::GetAlarmStatus() { return alarmstatus; }
void StatusBar::SetWiFiStatus(WIFI_STATUS status)   { wifistatus = status; }
StatusBar::WIFI_STATUS StatusBar::GetWiFiStatus()   { return wifistatus; }
void StatusBar::Enable() { _enabled = true; }
void StatusBar::Disable() { _enabled = false; }
bool StatusBar::Enabled() { return _enabled; }