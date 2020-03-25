#ifndef HANDLER
#define HANDLER

#include <Arduino.h>

struct Time
{
    uint64_t uptime;    // Uptime in milliseconds
    uint32_t time;      // Actual time
};

class IHandler {
    public:
        static void Handle(Time time);
};

#endif