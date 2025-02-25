#include "config.h"
#include "Encoder.h"

Encoder::Encoder(uint8_t clockPin, uint8_t dataPin, uint8_t btnPin, uint8_t instanceID)
: AiEsp32RotaryEncoder(dataPin, clockPin, btnPin, -1, 4)
{
    //setup(this->readEncoder_ISR);
    begin();
    enable();
}

void Encoder::SetCallback(encoder_callback callback)
{
    this->callback = callback;
}

void Encoder::Update()
{
    long newPos = readEncoder();
    if(lastPosition != newPos)
    {
        lastPosition = newPos;
        if(callback != NULL)
            callback(lastPosition);
    }
}