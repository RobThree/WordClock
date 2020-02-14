#include <Arduino.h>
#include <stdarg.h>
#include <clock.h>
#include <statusbar.h>

// Make sure each entry ends with a null terminator (0x00)!
byte(*WORDS[]) =
{
    /*  0: Twelve  */ (byte[]){ 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x00 },
    /*  1: One     */ (byte[]){ 0x2C, 0x2D, 0x2E, 0x00 },
    /*  2: Two     */ (byte[]){ 0x3B, 0x3A, 0x39, 0x38, 0x00 },
    /*  3: Three   */ (byte[]){ 0x34, 0x33, 0x32, 0x31, 0x00 },
    /*  4: Four    */ (byte[]){ 0x3D, 0x3E, 0x3F, 0x40, 0x00 },
    /*  5: Five    */ (byte[]){ 0x42, 0x43, 0x44, 0x45, 0x00 },
    /*  6: Six     */ (byte[]){ 0x51, 0x50, 0x4F, 0x00 },
    /*  7: Seven   */ (byte[]){ 0x4C, 0x4B, 0x4A, 0x49, 0x48, 0x00 },
    /*  8: Eight   */ (byte[]){ 0x53, 0x54, 0x55, 0x56, 0x00 },
    /*  9: Nine    */ (byte[]){ 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x00 },
    /* 10: Ten     */ (byte[]){ 0x66, 0x65, 0x64, 0x63, 0x00 },
    /* 11: Eleven  */ (byte[]){ 0x60, 0x5F, 0x5E, 0x00 },
    /* 12: It is   */ (byte[]){ 0x0F, 0x0E, 0x0D, 0x0B, 0X0A, 0x00 },
    /* 13: Five    */ (byte[]){ 0x08, 0x07, 0x06, 0x05, 0x00 },
    /* 14: Ten     */ (byte[]){ 0x11, 0x12, 0x13, 0x14, 0x00 },
    /* 15: To      */ (byte[]){ 0x25, 0x24, 0x23, 0x22, 0x00 },
    /* 16: Past    */ (byte[]){ 0x1F, 0x1E, 0x1D, 0x1C, 0x00 },
    /* 17: Quarter */ (byte[]){ 0x16, 0x17, 0x18, 0x19, 0x1A, 0x00 },
    /* 18: Half    */ (byte[]){ 0x27, 0x28, 0x29, 0x2A, 0x00 },
    /* 19: O'Clock */ (byte[]){ 0x70, 0x71, 0x72, 0x00 }
};

void Clock::TimestampToDisplay(long unixDateTime, bool useOffset = false)
{
    // Strip date part, keep time, apply offset when desired
    int time = (unixDateTime + (useOffset ? 150 : 0)) % 86400;
    int hour = time / 3600;       // Determine the hour
    int part = time % 3600 / 300; // Determine which part of the hour (truncated to 5 minutes)

    StatusBar::SetHeartStatus(unixDateTime & 0x01 ? StatusBar::HEART_STATUS::HS_BEAT : StatusBar::HEART_STATUS::HS_NONE);

    ShowWords(1, ITIS);
    switch (part)
    {
        case 0: break;
        case 1: ShowWords(2, FIVE, PAST); break;
        case 2: ShowWords(2, TEN, PAST); break;
        case 3: ShowWords(2, QUARTER, PAST); break;
        case 4: ShowWords(3, TEN, TO, HALF); break;
        case 5: ShowWords(3, FIVE, TO, HALF); break;
        case 6: ShowWords(1, HALF); break;
        case 7: ShowWords(3, FIVE, PAST, HALF); break;
        case 8: ShowWords(3, TEN, PAST, HALF); break;
        case 9: ShowWords(2, QUARTER, TO); break;
        case 10: ShowWords(2, TEN, TO); break;
        case 11: ShowWords(2, FIVE, TO); break;
    }

    // Add hour
    ShowWords(1, (WORD)((hour + (part > 3 ? 1 : 0)) % 12));

    // On the whole hour, we need to add "o'clock"
    if (part == 0)
        ShowWords(1, HOUR);
}

void Clock::ShowWords(int argcount, ...)
{
    va_list arguments;
    va_start(arguments, argcount);
    // Iterate the words
    for (int i = 0; i < argcount; i++)
    {
        int wordindex = va_arg(arguments, int);

        for (byte *c = WORDS[wordindex]; *c != 0; c++)
            Display::SetLED(*c, CRGB::White);
        
        va_end(arguments);
    }
}