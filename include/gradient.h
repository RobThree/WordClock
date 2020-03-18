#ifndef GRADIENT_H
#define GRADiENT_H

#include <display.h>
#include <ihandler.h>

class Gradient : public IHandler
{
public:
    static void Initialize(CRGB from, CRGB to);
    static void Handle(HandlerInfo info);
private:
};
#endif