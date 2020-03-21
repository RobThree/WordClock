#include <config.h>
#include <animation.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

uint16_t frameCount = 0;
uint16_t currentFrame = 0;
uint32_t lastTime = 0;
uint8_t data = 0;
uint8_t totalleds;

typedef struct
{
    uint16_t delay;
    CRGB pixels[110];
} AnimationFrame;

AnimationFrame* frames;

void Animation::Initialize(String url) {
    totalleds = Display::GetTotalScreenLeds();

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
            frames = new AnimationFrame[frameCount];
            uint16_t width = (buffer[3] << 8) + buffer[2];
            uint16_t height = (buffer[5] << 8) + buffer[4];

            for (uint8_t i = 0; i < frameCount; i++) {
                // offset = number of frames, times 110 pixels, times 3 bytes per pixel, plus six header bytes, plus two header bytes per previous frame
                uint16_t offset = i * 110 * 3 + 6 + (i * 2);
                uint16_t delay = (buffer[offset + 1] << 8) + buffer[offset];
                frames[i].delay = delay;

                // offset the current header
                offset += 2;
                for (uint8_t y = 0; y < height; y++) {
                    for (uint8_t x = 0; x < width; x++) {
                        uint16_t pixel = (y * width + x) * 3 + offset;
                        frames[i].pixels[y * width + x].setRGB(buffer[pixel], buffer[pixel + 1], buffer[pixel + 2]);
                    }
                }
            }
        }
    }
}

void Animation::Handle(HandlerInfo info) {
    // Initialize lastTime
    if (lastTime == 0) {
        lastTime = info.uptime;
        return;
    }

    for (uint8_t i = 0; i < totalleds; i++)
        Display::SetLED(i, frames[currentFrame].pixels[i]);

    // Wait until delay is passed, then increase currentFrame
    // TODO: handle overshoot when frameTime and frameRate are not compatible
    if (info.uptime - lastTime >= frames[currentFrame].delay) { 
        if (currentFrame < frameCount - 1) {
            currentFrame++;
        } else {
            currentFrame = 0;
        }
        lastTime = info.uptime;
    }
}