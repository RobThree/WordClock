#include <ota.h>
#include <ArduinoOTA.h>
#include <config.h>
#include <statusbar.h>
#include <display.h>

void OTA::Initialize() {
    Serial.println("Initializing OTA");
    ArduinoOTA.setHostname(OTA_HOSTNAME);
    ArduinoOTA.setPassword((const char *)OTA_PASSWORD);
    ArduinoOTA.setPort(OTA_PORT);
    ArduinoOTA.onStart([]() {
        Serial.println("Start");
        StatusBar::SetWiFiStatus(StatusBar::WIFI_STATUS::WS_OTASTART);
        Display::Refresh();
    });
    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
        StatusBar::SetWiFiStatus(StatusBar::WIFI_STATUS::WS_OTACOMPLETE);
        Display::Refresh();
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        uint progresspercentage = (progress / (total / 100));
        Serial.printf("Progress: %u%%\r", progresspercentage);
        for (int i=0;i< map(progresspercentage, 0, 100, 0, Display::GetTotalScreenLeds());i++)
            Display::SetLED(i, CHSV(map(progresspercentage, 0, 100, 0, 255), 255, 255));
        StatusBar::SetWiFiStatus(StatusBar::WIFI_STATUS::WS_OTAPROGRESS);
        Display::Refresh();
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        StatusBar::SetWiFiStatus(StatusBar::WIFI_STATUS::WS_OTAERROR);
        Display::Refresh();
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
        delay(2000);    // Make sure the status can be seen
    });
    ArduinoOTA.begin();
    Serial.println("OTA initialized");
}

void OTA::Handle() {
    ArduinoOTA.handle();
}