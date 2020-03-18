#ifndef SOLIDCOLOR_H
#define SOLIDCOLOR_H

#include <display.h>
#include <ihandler.h>

class SolidColor : public IHandler
{
public:
    static void Initialize(CRGB color);
    static void Handle(HandlerInfo info);
private:
};
#endif