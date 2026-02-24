/*
 * @file button.c
 * @brief Bonbon-Automat State Machine
 * @brief Copyright 2025 Beaurel Ingride Ngaleu
 */


#include "button.h"

#define BUTTON_PORT   GpioC
#define BUTTON_PIN    13

// Global pin structure (if you want to use the simple API)
static GpioPin_t buttonPin = { BUTTON_PORT, BUTTON_PIN };

void Button_Init(void) {
    // Input mode, with pull-up (button active-low)
    bmlGpioInitFull(buttonPin, GPIO_MODE_INPUT, GPIO_PULLUP);
}

int Button_IsPressed(void) {
    // Return 1 if pressed (low), 0 if not pressed
    return (bmlGpioReadSimple(buttonPin) == GPIO_LOW) ? 1 : 0;
}
