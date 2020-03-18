// COPY THIS FILE AND RENAME IT TO "config.h" AND ENTER ALL YOUR CONFIGURATION DATA BELOW

#ifndef CONFIG_H
#define CONFIG_H

// Replace with your actual SSID and password:
#define WIFI_SSID           "Your SSID here"
#define WIFI_PASSWD         "WLAN AP password here"
#define WIFI_CONNECTTIMEOUT 60000

#define OTA_HOSTNAME    "wordclock"
#define OTA_PASSWORD    "my_ota_secret" // See example_env_secrets.ini / env_secrets.ini
#define OTA_PORT        8266

// Replace with your actual timezone:
#define NTP_HOST        "pool.ntp.org"
#define NTP_TIMEZONE    "Europe/Amsterdam"
#define NTP_SYNCINTERVAL 1800           // In seconds

// LED display properties
#define DISPLAY_LED_PIN         D2
#define DISPLAY_ROWS            10
#define DISPLAY_COLS            11
#define DISPLAY_NUM_STATUSLEDS  5
#define DISPLAY_NUM_LEDS_SCREEN DISPLAY_ROWS * DISPLAY_COLS
#define DISPLAY_NUM_LEDS_TOTAL  DISPLAY_NUM_LEDS_SCREEN + DISPLAY_NUM_STATUSLEDS
#define DISPLAY_LED_TYPE        WS2812B
#define DISPLAY_COLOR_ORDER     GRB

// LDR settings
#define LDR_PIN                 A0
#define LDR_DARK                64      // Brightness for dark environment
#define LDR_LIGHT               255     // Brightness for bright light environment
#define LDR_FADE_TIME           10000   // How long to take when adjusting brightness (in ms)

// Define status LED indices
#define STATUSLED_CLOCK     0x00
#define STATUSLED_HEART     0x01
#define STATUSLED_PARTY     0x02
#define STATUSLED_ALARM     0x03
#define STATUSLED_WIFI      0x04

// Clock settings
#define CLOCK_USEROUNDING   true    // Will round to the nearest 5 minutes instead of switching at exact time
#define CLOCK_FPS           25      // Number of (desired) frames per second, no guarantees
#define SERIAL_SPEED        460800
#endif