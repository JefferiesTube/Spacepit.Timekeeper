#include <Arduino.h>

#include "config.h"

#include "util/time.h"
#include "displays/UptimeDisplay.h"
#include "displays/Countdown.h"
#include "AiEsp32RotaryEncoder.h"

#include <Bounce2.h>

AiEsp32RotaryEncoder encoder(ENCODER_DATA, ENCODER_CLK, ENCODER_BTN, 1, 4);

UptimeDisplay uptimeDisplay(CLK, DIOA);

CountdownDisplay countdownA(CLK, DIOC);
CountdownDisplay countdownB(CLK, DIOD);
bool useCountdownA = true;

Bounce2::Button toggleButton = Bounce2::Button();
Bounce2::Button resetButton = Bounce2::Button();

uint32_t selTime = 0;

void Callback(uint32_t newValue)
{
  selTime = newValue;  
}

void IRAM_ATTR readEncoderISR()
{
    encoder.readEncoder_ISR();
}

void IRAM_ATTR readEncoderButton()
{
    //uptime = 0;
}

void IRAM_ATTR SelectorChanged()
{
    auto selection = digitalRead(SELECTOR);
    useCountdownA = selection == LOW;
}

void IRAM_ATTR ToggleTimer()
{
    auto countdown = useCountdownA ? countdownA : countdownB;
    countdown.Toggle();
}

void IRAM_ATTR ResetTimer()
{
    auto countdown = useCountdownA ? countdownA : countdownB;
    countdown.Reset();
}

void setup() 
{
  Serial2.begin(9600, SERIAL_8N1, GPIO_NUM_23, GPIO_NUM_22, false);
  delay(1000);
  while(!Serial2);
  
  pinMode(ENCODER_BTN, INPUT_PULLDOWN);
  pinMode(SELECTOR, INPUT);
  pinMode(BTN_TOGGLE, INPUT_PULLUP);
  pinMode(BTN_RESET, INPUT_PULLUP);

  attachInterrupt(SELECTOR, SelectorChanged, CHANGE);
  //attachInterrupt(BTN_TOGGLE, ToggleTimer, FALLING);
  //attachInterrupt(BTN_RESET, ResetTimer, FALLING);  
  toggleButton.attach(BTN_TOGGLE, INPUT_PULLUP);
  toggleButton.interval(5);
  toggleButton.setPressedState(LOW);
  resetButton.attach(BTN_RESET, INPUT_PULLUP);
  resetButton.interval(5);
  resetButton.setPressedState(LOW);

  Serial2.println("Startup complete");
  encoder.begin();
  encoder.setup(readEncoderISR, readEncoderButton);
  encoder.setBoundaries(0, 3599, false);
  encoder.setAcceleration(100);
}

void loop() 
{
  Serial2.println("loop");
  delay(500);

  toggleButton.update();
  if(toggleButton.isPressed())
  {
    auto countdown = useCountdownA ? countdownA : countdownB;
    countdown.Toggle();
    Serial2.println("TOGGLE");
  }

  resetButton.update();
  if(resetButton.isPressed())
  {
    auto countdown = useCountdownA ? countdownA : countdownB;
    countdown.Reset();
    Serial2.println("RESET");
  }

  uptimeDisplay.Update();
  countdownA.Update();
  countdownB.Update();
  //uptime = encoder.readEncoder();
}
