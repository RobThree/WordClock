#include <Arduino.h>
#include <stdarg.h>
#include <clock.h>
#include <statusbar.h>

// Words defined as (startindex, length)
uint8_t WORDS[] =
{
    /*  0: Twelve  */ 0x63, 0x06,
    /*  1: One     */ 0x27, 0x03,
    /*  2: Two     */ 0x2C, 0x04,
    /*  3: Three   */ 0x33, 0x04,
    /*  4: Four    */ 0x38, 0x04,
    /*  5: Five    */ 0x3D, 0x04,
    /*  6: Six     */ 0x42, 0x03,
    /*  7: Seven   */ 0x47, 0x05,
    /*  8: Eight   */ 0x4E, 0x04,
    /*  9: Nine    */ 0x53, 0x05,
    /* 10: Ten     */ 0x59, 0x04,
    /* 11: Eleven  */ 0x5F, 0x03,
    /* 12: It      */ 0x00, 0x03,
    /* 13: Is      */ 0x04, 0x02,
    /* 14: Five    */ 0x07, 0x04,
    /* 15: Ten     */ 0x0C, 0x04,
    /* 16: To      */ 0x16, 0x04,
    /* 17: Past    */ 0x1C, 0x04,
    /* 18: Quarter */ 0x11, 0x05,
    /* 19: Half    */ 0x22, 0x04,
    /* 20: O'Clock */ 0x6B, 0x03,
};

void Clock::TimestampToDisplay(uint32_t unixDateTime, bool useOffset = false)
{
    // Strip date part, keep time, apply offset when desired
    uint32_t time = (unixDateTime + (useOffset ? 150 : 0)) % 86400;
    uint8_t hour = time / 3600;       // Determine the hour
    uint8_t part = time % 3600 / 300; // Determine which part of the hour (truncated to 5 minutes)

    ShowWords(2, IT, IS);
    switch (part)
    {
        case 0:  break;
        case 1:  ShowWords(2, FIVE, PAST); break;
        case 2:  ShowWords(2, TEN, PAST); break;
        case 3:  ShowWords(2, QUARTER, PAST); break;
        case 4:  ShowWords(3, TEN, TO, HALF); break;
        case 5:  ShowWords(3, FIVE, TO, HALF); break;
        case 6:  ShowWords(1, HALF); break;
        case 7:  ShowWords(3, FIVE, PAST, HALF); break;
        case 8:  ShowWords(3, TEN, PAST, HALF); break;
        case 9:  ShowWords(2, QUARTER, TO); break;
        case 10: ShowWords(2, TEN, TO); break;
        case 11: ShowWords(2, FIVE, TO); break;
    }

    // Add hour
    ShowWords(1, (WORD)((hour + (part > 3 ? 1 : 0)) % 12));

    // On the whole hour, we need to add "o'clock"
    if (part == 0)
        ShowWords(1, HOUR);
}

void Clock::ShowWords(uint8_t argcount, ...)
{
    va_list arguments;
    va_start(arguments, argcount);
    // Iterate the words
    for (uint8_t i = 0; i < argcount; i++)
    {
        uint8_t wordindex = va_arg(arguments, int) * 2;
        uint8_t wordstart = WORDS[wordindex];
        uint8_t wordlen = WORDS[wordindex + 1];

        for (uint8_t c = 0; c < wordlen; c++)
            Display::SetLED(wordstart + c, CRGB::White);
        
        va_end(arguments);
    }
}