#pragma once

#include <Arduino.h>
#include "TM1637Display.h"


enum BrightnessLevel { Lowest = 0, Low = 1, BelowNormal = 2, Normal = 3, AboveNormal = 4, High = 5, Higher = 6, Highest = 7 };

class SegmentedDisplay : public TM1637Display
{
public:
    SegmentedDisplay(uint8_t clock, uint8_t data) : TM1637Display(clock, data)
    {
        setBrightness(BrightnessLevel::Lowest);
    }

    uint8_t getDotMask(const bool dotA, const bool dotB, const bool dotC, const bool dotD)
    {
        uint8_t res = 0;
        res |= dotA ? (0x80 >> 0) : 0;
        res |= dotB ? (0x80 >> 1) : 0;
        res |= dotC ? (0x80 >> 2) : 0;
        res |= dotD ? (0x80 >> 3) : 0;
        return res;
    }
};