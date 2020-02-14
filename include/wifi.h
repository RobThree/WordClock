#ifndef WIFI_H
#define WIFI_H

#include <statusbar.h>
#include <ESP8266WiFi.h>

class WIFI
{
public:
    static void Initialize();
    static void UpdateStatus();
private:
    static StatusBar::WIFI_STATUS MapWiFiStatus(wl_status_t status);
};
#endif