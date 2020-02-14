#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>
#include <Display.h>

class Clock
{
private:
    enum WORD
    {
        DIGIT_12,
        DIGIT_1,
        DIGIT_2,
        DIGIT_3,
        DIGIT_4,
        DIGIT_5,
        DIGIT_6,
        DIGIT_7,
        DIGIT_8,
        DIGIT_9,
        DIGIT_10,
        DIGIT_11,
        ITIS,
        FIVE,
        TEN,
        TO,
        PAST,
        QUARTER,
        HALF,
        HOUR
    };

public:
    static void TimestampToDisplay(long unixDateTime, bool useOffset);

private:
    static void ShowWords(int argcount, ...);
};

#endif