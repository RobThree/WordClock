#include <config.h>
#include <animation.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <statusbar.h>

uint16_t frameCount = 0;
uint16_t currentFrame = 0;
uint16_t frameTime = 1000;
long lastTime = 0;
uint8_t data = 0;

#define max(a,b) ((a)>(b)?(a):(b))

typedef struct
{
    uint32_t pixels[110];
} AnimationFrame;

AnimationFrame frames[60];


void Animation::SetAnimation(String url) {
    Serial.println("Setting animation...");
    delay(1000);
    // fixed frametime, for now
    // right now the delay (16 bytes) isn't loaded and is included in the offset.
    frameTime = 250;

    WiFiClient client;
    HTTPClient http;
    if (http.begin(client, url)) {
        int httpCode = http.GET();
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_FOUND) {
            uint8_t buffer[http.getSize()];
            client.readBytes(buffer, sizeof(buffer));

            // framecount, width, height and delay are 16 bytes
            // little endian order in buffer!
            frameCount = (buffer[1] << 8) + buffer[0];
            uint16_t width = (buffer[3] << 8) + buffer[2];
            uint16_t height = (buffer[5] << 8) + buffer[4];

            for (int i = 0; i < frameCount; i++) {
                Serial.printf("frame %d...\r\n", i);
                // offset = number of frames, times 110 pixels, times 3 bytes per pixel, plus six header bytes, plus two header bytes per frame
                int offset = i * 110 * 3 + 6 + ((i + 1) * 2);
                for (int y = 0; y < height; y++) {
                    for (int x = 0; x < width; x++) {
                        int pixel = (y * width + x) * 3 + offset;
                        CRGB rgb;
                        rgb.setRGB(buffer[pixel + 2], buffer[pixel + 1], buffer[pixel]);

                        // led strip direction is back and forth over rows
                        // excluding the status leds, even rows are right to left, odd rows are left to right
                        if (y % 2 == 0) {
                            memcpy(&frames[i].pixels[(y * width) + width - 1 - x], &rgb, sizeof(rgb));
                        } else{
                            memcpy(&frames[i].pixels[y * width + x], &rgb, sizeof(rgb));
                        }
                    }
                }
                Serial.printf("frame %d done!\r\n", i);
                delay(1000);
            }
        }
    }
}

void Animation::SetAnimationFrame(long time) {
    // initialize lastTime
    if (lastTime == 0) {
        lastTime = time;
        return;
    }

    for (int i = 0; i < DISPLAY_NUM_LEDS - DISPLAY_NUM_STATUSLEDS; i++) {
        //CRGB newPixel = frames[currentFrame].pixels[i];
        //newPixel.setRGB(max(0, newPixel.r - 100), max(0, newPixel.g - 100), max(0, newPixel.b - 100));
        Display::SetLED(i + DISPLAY_NUM_STATUSLEDS, frames[currentFrame].pixels[i]);
    }

    // wait untill frametime is passed, then increase currentFrame
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