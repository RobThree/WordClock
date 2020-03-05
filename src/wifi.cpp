#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <wifi.h>
#include <config.h>
#include <statusbar.h>
#include <display.h>

const char* wifi_ssid = WIFI_SSID;
const char* wifi_pass = WIFI_PASSWD;

WiFiEventHandler gotIpEventHandler, disconnectedEventHandler;

void WIFI::Initialize() {

    WiFi.mode(WIFI_STA);

    // Update status when we get a connection
    gotIpEventHandler = WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP& event)
    {
        Serial.printf("Station connected, IP: %s", WiFi.localIP().toString().c_str());
        WIFI::UpdateStatus();
    });

    // Reconnect on disconnect
    disconnectedEventHandler = WiFi.onStationModeDisconnected([](const WiFiEventStationModeDisconnected& event)
    {
        Serial.println("Station disconnected");
        WIFI::UpdateStatus();
        delay(5000);
        Connect();
    });
    
    // Now connect
    Connect();

    // On initial startup we want to block before we return
    if (WiFi.waitForConnectResult(WIFI_CONNECTTIMEOUT) != WL_CONNECTED) {
        WIFI::UpdateStatus();
        Serial.println("Unable to connect");
        delay(5000);
        ESP.restart();
    }
}

void WIFI::Connect() {
    StatusBar::SetWiFiStatus(StatusBar::WIFI_STATUS::WS_CONNECTING);
    Display::Refresh();
    Serial.printf("Connecting to %s...\n", wifi_ssid);
    WiFi.begin(wifi_ssid, wifi_pass);
}

void WIFI::UpdateStatus() {
    StatusBar::SetWiFiStatus(MapWiFiStatus(WiFi.status()));
    Display::Refresh();
}

StatusBar::WIFI_STATUS WIFI::MapWiFiStatus(wl_status_t status) {
  switch (status) {
    // case WL_NO_SHIELD:          return StatusBar::WIFI_STATUS::WS_NONE;
    // case WL_IDLE_STATUS:        return StatusBar::WIFI_STATUS::WS_NONE;
    // case WL_NO_SSID_AVAIL:      return StatusBar::WIFI_STATUS::WS_NONE;
    // case WL_SCAN_COMPLETED:     return StatusBar::WIFI_STATUS::WS_NONE;
    case WL_CONNECTED:          return StatusBar::WIFI_STATUS::WS_CONNECTED;
    // case WL_CONNECT_FAILED:     return StatusBar::WIFI_STATUS::WS_DISCONNECTED;
    // case WL_CONNECTION_LOST:    return StatusBar::WIFI_STATUS::WS_DISCONNECTED;
    // case WL_DISCONNECTED:       return StatusBar::WIFI_STATUS::WS_DISCONNECTED;
    default:
      return StatusBar::WIFI_STATUS::WS_DISCONNECTED;
  }
}