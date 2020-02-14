#include <statusbar.h>

StatusBar::CLOCK_STATUS clockstatus;
StatusBar::HEART_STATUS heartstatus;
StatusBar::PARTY_STATUS partystatus;
StatusBar::ALARM_STATUS alarmstatus;
StatusBar::WIFI_STATUS  wifistatus;

void StatusBar::Initialize() {
    SetClockStatus(StatusBar::CLOCK_STATUS::CS_NONE);
    SetHeartStatus(StatusBar::HEART_STATUS::HS_NONE);
    SetPartyStatus(StatusBar::PARTY_STATUS::PS_NONE);
    SetAlarmStatus(StatusBar::ALARM_STATUS::AS_NONE);
    SetWiFiStatus (StatusBar::WIFI_STATUS::WS_NONE);
}

void StatusBar::SetClockStatus(CLOCK_STATUS status) { clockstatus = status; }
StatusBar::CLOCK_STATUS StatusBar::GetClockStatus() { return clockstatus; }
void StatusBar::SetHeartStatus(HEART_STATUS status) { heartstatus = status; }
StatusBar::HEART_STATUS StatusBar::GetHeartStatus() { return heartstatus;  }
void StatusBar::SetPartyStatus(PARTY_STATUS status) { partystatus = status; }
StatusBar::PARTY_STATUS StatusBar::GetPartyStatus() { return partystatus; }
void StatusBar::SetAlarmStatus(ALARM_STATUS status) { alarmstatus = status; }
StatusBar::ALARM_STATUS StatusBar::GetAlarmStatus() { return alarmstatus; }
void StatusBar::SetWiFiStatus(WIFI_STATUS status)   { wifistatus = status; }
StatusBar::WIFI_STATUS StatusBar::GetWiFiStatus()   { return wifistatus; }