#ifndef WIFI_H
#define WIFI_H

#include <statusbar.h>
#include <ESP8266WiFi.h>

class WIFI
{
public:
    static void Initialize();
private:
    static void Connect();
    static void UpdateStatus();
    static StatusBar::WIFI_STATUS MapWiFiStatus(wl_status_t status);
};
#endif