#ifndef RAINBOW_H
#define RAINBOW_H

#include <display.h>
#include <ihandler.h>

class Rainbow : public IHandler
{
public:
    static void Initialize(uint8_t brightnesss, uint8_t stepspersecond);
    static void Handle(Time time);
private:
};
#endif