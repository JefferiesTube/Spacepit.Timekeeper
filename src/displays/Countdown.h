#pragma once

#include "SegmentedDisplay.h"
#include "TM1637Display.h"
#include <arduino-timer.h>
#include <util/time.h>
#include "config.h"

class CountdownDisplay : public SegmentedDisplay
{
  private:
    Timer<1, millis> timer;
    uint64_t remainingSeconds = 60;
    bool isActive = false;

    static bool advanceCountdown(void* target)
    {
      auto uptimeDisplay = reinterpret_cast<CountdownDisplay*>(target);
      if(!uptimeDisplay->isActive)
        return true;

      uptimeDisplay->remainingSeconds--;
      uptimeDisplay->RenderTime();
      return true;
    }

    void AutoSetBrightness()
    {
      setBrightness(isActive ? BrightnessLevel::Normal : BrightnessLevel::Lowest);
      RenderTime();
    }

    void RenderTime()
    {
      showNumberDecEx(FormatSecondsAsTime(remainingSeconds), getDotMask(false, remainingSeconds % 2 == 0, false, false), true);
    }

  public:
    CountdownDisplay(uint8_t clk, uint8_t data) : SegmentedDisplay(clk, data)
    {
      timer.every(1000, advanceCountdown, this);
      RenderTime();
    }

    void Toggle()
    {
      isActive = !isActive;
      AutoSetBrightness();
    }

    void SetActive(bool newState)
    {
      isActive = newState;
      AutoSetBrightness();
    }

    void Reset()
    {
      isActive = false;
      AutoSetBrightness();
      remainingSeconds = 0;
      RenderTime();
    }

    void SetRemainingTime(uint64_t seconds)
    {
      remainingSeconds = seconds;
      RenderTime();
    }

    void Update()
    {
        timer.tick();
    }
};
