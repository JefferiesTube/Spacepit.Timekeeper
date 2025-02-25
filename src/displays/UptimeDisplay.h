#pragma once

#include "SegmentedDisplay.h"
#include "TM1637Display.h"
#include <arduino-timer.h>
#include <util/time.h>
#include "config.h"

class UptimeDisplay : public SegmentedDisplay
{
  private:
    Timer<1, millis> timer;
    uint64_t uptime = 0;

    static bool advanceTime(void* target)
    {
      auto uptimeDisplay = reinterpret_cast<UptimeDisplay*>(target);
      uptimeDisplay->uptime++;
      uptimeDisplay->showNumberDecEx(FormatSecondsAsTime(uptimeDisplay->uptime), uptimeDisplay->getDotMask(false, uptimeDisplay->uptime % 2 == 0, false, false), true);
      Serial.println("WUPP");
      return true;
    }

  public:
    UptimeDisplay(uint8_t clk, uint8_t data) : SegmentedDisplay(clk, data)
    {
      timer.every(1000, advanceTime, this);
    }

    void Update()
    {
        timer.tick();
    }
};
