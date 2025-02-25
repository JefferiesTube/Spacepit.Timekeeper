#pragma once

#include <Arduino.h>
#include "AiEsp32RotaryEncoder.h"

typedef void (*encoder_callback)(uint32_t);

class Encoder : public AiEsp32RotaryEncoder
{
    private:
        encoder_callback callback;
        long lastPosition = 0;
    public:
        Encoder(uint8_t clockPin, uint8_t dataPin, uint8_t btnPin, uint8_t instanceID);
        void SetCallback(encoder_callback callback);
        void Update();
};