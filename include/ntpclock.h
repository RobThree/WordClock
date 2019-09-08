#ifndef NTPCLOCK_H
#define NTPCLOCK_H

#include <ezTime.h>

class NTPClock
{
public:
    static void Initialize();
    static long Now();
};
#endif