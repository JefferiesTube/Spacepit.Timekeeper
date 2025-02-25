#pragma once

#include <Arduino.h>

//////// Segment Display ////////

const uint8_t CLK = GPIO_NUM_32;
const uint8_t DIOA = GPIO_NUM_25;
const uint8_t DIOB = GPIO_NUM_33;
const uint8_t DIOC = GPIO_NUM_26;
const uint8_t DIOD = GPIO_NUM_27;

//////// Rotary Encoder ////////

const uint8_t ENCODER_CLK = GPIO_NUM_4;
const uint8_t ENCODER_DATA = GPIO_NUM_15;
const uint8_t ENCODER_BTN = GPIO_NUM_16;

//////// Selector Switch ////////

const uint8_t SELECTOR = GPIO_NUM_14;

//////// Button Inputs ////////

const uint8_t BTN_TOGGLE = GPIO_NUM_18;
const uint8_t BTN_RESET = GPIO_NUM_19;
