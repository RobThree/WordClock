#ifndef ANIMATION_H
#define ANIMATION_H

#include <display.h>
#include <ihandler.h>

class Animation : public IHandler
{
public:
    static void Initialize(String url);
    static void Handle(Time time);
private:
};
#endif