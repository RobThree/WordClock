#ifndef HANDLER
#define HANDLER

#include <Arduino.h>

struct HandlerInfo
{
    uint32_t uptime;    // Uptime in milliseconds
    uint32_t time;      // Actual time
};

class IHandler {
    public:
        static void Handle(HandlerInfo info);
};

#endif