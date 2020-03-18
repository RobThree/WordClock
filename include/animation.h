#ifndef ANIMATION_H
#define ANIMATION_H

#include <display.h>

class Animation
{
public:
    static void Initialize(String url);
    static void SetAnimationFrame(uint32_t time);
private:
};
#endif