#include <config.h>
#include <animation.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <statusbar.h>

uint16_t frameCount = 0;
uint16_t currentFrame = 0;
uint16_t frameTime = 1000;
uint32_t lastTime = 0;
uint8_t data = 0;
uint8_t totalleds;

#define max(a,b) ((a)>(b)?(a):(b))

typedef struct
{
    uint32_t pixels[110];
} AnimationFrame;

AnimationFrame frames[60];


void Animation::Initialize(String url) {
    totalleds = Display::GetTotalScreenLeds();

    // Fixed frametime, for now
    // Right now the delay (16 bytes) isn't loaded and is included in the offset.
    frameTime = 250;

    WiFiClient client;
    HTTPClient http;
    if (http.begin(client, url)) {
        uint16_t httpCode = http.GET();
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_FOUND) {
            uint8_t buffer[http.getSize()];
            client.readBytes(buffer, sizeof(buffer));

            // Framecount, width, height and delay are 16 bytes
            // Little endian order in buffer!
            frameCount = (buffer[1] << 8) + buffer[0];
            uint16_t width = (buffer[3] << 8) + buffer[2];
            uint16_t height = (buffer[5] << 8) + buffer[4];

            for (uint8_t i = 0; i < frameCount; i++) {
                // offset = number of frames, times 110 pixels, times 3 bytes per pixel, plus six header bytes, plus two header bytes per frame
                uint16_t offset = i * 110 * 3 + 6 + ((i + 1) * 2);
                for (uint8_t y = 0; y < height; y++) {
                    for (uint8_t x = 0; x < width; x++) {
                        uint16_t pixel = (y * width + x) * 3 + offset;
                        CRGB rgb;
                        rgb.setRGB(buffer[pixel + 2], buffer[pixel + 1], buffer[pixel]);

                        memcpy(&frames[i].pixels[y * width + x], &rgb, sizeof(rgb));
                    }
                }
            }
        }
    }
}

void Animation::SetAnimationFrame(uint32_t time) {
    // Initialize lastTime
    if (lastTime == 0) {
        lastTime = time;
        return;
    }

    for (uint8_t i = 0; i < totalleds; i++)
        Display::SetLED(i, frames[currentFrame].pixels[i]);

    // Wait until frametime is passed, then increase currentFrame
    // TODO: handle overshoot when frameTime and frameRate are not compatible
    if (time - lastTime >= frameTime) { 
        if (currentFrame < frameCount - 1) {
            currentFrame++;
        } else {
            currentFrame = 0;
        }
        lastTime = time;
    }
}