#pragma once

#include <Arduino.h>

int FormatSecondsAsTime(uint64_t totalSeconds)
{
  // uint16_t hours = totalSeconds / 3600;
  totalSeconds %= 3600;
  uint16_t minutes = totalSeconds / 60;
  uint16_t seconds = totalSeconds % 60;
  return (minutes * 100) + seconds;
}