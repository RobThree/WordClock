#include <config.h>
#include <animation.h>
#include "FS.h"
#include <LittleFS.h>

uint16_t _framecount = 0;
uint16_t _currentframe = 0;
uint64_t _nexttime = 0;
uint8_t _totalleds;

typedef struct
{
    uint16_t delay;
    CRGB pixels[110];
} AnimationFrame;

AnimationFrame* frames;

void Animation::Initialize(const String filename) {
    _totalleds = Display::GetTotalScreenLeds();

    if (!LittleFS.begin()) {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }

    File file = LittleFS.open(filename, "r");
    if(!file){
        Serial.printf("There was an error opening file %s for reading\n", filename.c_str());
        return;
    }

    size_t size = file.size();
    uint8_t buffer[size];
    size_t pos = 0;

    while (pos < size) {
        size_t bytes_read = file.read(buffer + pos, size - pos);
        pos += bytes_read;
        Serial.print(".");
    }

    Serial.printf("\nRead %d bytes\n", size);
    file.close();
    LittleFS.end();

    // Framecount, width, height and delay are 16 bytes
    // Little endian order in buffer!
    _framecount = (buffer[1] << 8) + buffer[0];
    frames = new AnimationFrame[_framecount];
    uint16_t width = (buffer[3] << 8) + buffer[2];
    uint16_t height = (buffer[5] << 8) + buffer[4];

    for (uint8_t i = 0; i < _framecount; i++) {
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

void Animation::Handle(Time time) {
    for (uint8_t i = 0; i < _totalleds; i++)
        Display::SetLED(i, frames[_currentframe].pixels[i]);

    // Time for a new frame?
    if (time.uptime >= _nexttime) {
        // Determine when to display next frame
        _nexttime = time.uptime + frames[_currentframe].delay;
        // Advance frame
        _currentframe = (_currentframe + 1) % _framecount;
    }
}