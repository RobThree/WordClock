#include <Arduino.h>
#include <stdarg.h>
#include <clock.h>

// TODO: Put in actual addresses of LEDs
// Make sure each entry ends with a null terminator (0x00)!
byte(*WORDS[]) =
    {
        /*  0: Twelve  */ (byte[]){0x54, 0x77, 0x61, 0x61, 0x6c, 0x66, 0x00},
        /*  1: One     */ (byte[]){0x45, 0x65, 0x6e, 0x00},
        /*  2: Two     */ (byte[]){0x54, 0x77, 0x65, 0x65, 0x00},
        /*  3: Three   */ (byte[]){0x44, 0x72, 0x69, 0x65, 0x00},
        /*  4: Four    */ (byte[]){0x56, 0x69, 0x65, 0x72, 0x00},
        /*  5: Five    */ (byte[]){0x56, 0x69, 0x6a, 0x66, 0x00},
        /*  6: Six     */ (byte[]){0x5a, 0x65, 0x73, 0x00},
        /*  7: Seven   */ (byte[]){0x5a, 0x65, 0x76, 0x65, 0x6e, 0x00},
        /*  8: Eight   */ (byte[]){0x41, 0x63, 0x68, 0x74, 0x00},
        /*  9: Nine    */ (byte[]){0x4e, 0x65, 0x67, 0x65, 0x6e, 0x00},
        /* 10: Ten     */ (byte[]){0x54, 0x69, 0x65, 0x6e, 0x00},
        /* 11: Eleven  */ (byte[]){0x45, 0x6c, 0x66, 0x00},
        /* 12: It is   */ (byte[]){0x48, 0x65, 0x74, 0x20, 0x69, 0x73, 0x00},
        /* 13: Five    */ (byte[]){0x56, 0x69, 0x6a, 0x66, 0x00},
        /* 14: Ten     */ (byte[]){0x54, 0x69, 0x65, 0x6e, 0x00},
        /* 15: To      */ (byte[]){0x56, 0x6f, 0x6f, 0x72, 0x00},
        /* 16: Past    */ (byte[]){0x4f, 0x76, 0x65, 0x72, 0x00},
        /* 17: Quarter */ (byte[]){0x4b, 0x77, 0x61, 0x72, 0x74, 0x00},
        /* 18: Half    */ (byte[]){0x48, 0x61, 0x6c, 0x66, 0x00},
        /* 19: O'Clock */ (byte[]){0x55, 0x75, 0x72, 0x00}};

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

void TimestampToLEDS(long unixDateTime, bool useOffset = false)
{
    // Strip date part, keep time, apply offset when desired
    int time = (unixDateTime + (useOffset ? 150 : 0)) % 86400;
    int hour = time / 3600;       // Determine the hour
    int part = time % 3600 / 300; // Determine which part of the hour (truncated to 5 minutes)

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

void ClearLeds()
{
    //TODO: Clear all LEDS
}

void ShowWords(int argcount, ...)
{
    va_list arguments;
    va_start(arguments, argcount);
    // Iterate the words
    for (int i = 0; i < argcount; i++)
    {
        int wordindex = va_arg(arguments, int);
        //TODO: Iterate the addresses and set the individual LEDs
        for (byte *c = WORDS[wordindex]; *c != 0; c++)
            Serial.print((char)*c);
        Serial.print(" ");
        va_end(arguments);
    }
}