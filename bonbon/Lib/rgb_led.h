/*
 * @file rgb_led.h
 * @brief Bonbon-Automat State Machine
 * @brief Copyright 2025 Beaurel Ingride Ngaleu
 */


#ifndef RGB_LED_H
#define RGB_LED_H

#include <stdint.h>

typedef enum {
    RGB_STATE_OFF,
    RGB_STATE_OK,       // Grün
    RGB_STATE_LOW,      // Rot
    RGB_STATE_MOVING    // Blau
} RgbState_t;

void rgb_led_init(void);
void rgb_led_set_color(uint8_t r, uint8_t g, uint8_t b);
void rgb_led_set_state(RgbState_t state);
void rgb_led_state_blau(void);
void rgb_led_state_gruen(void);
void rgb_led_state_rot(void);

#endif // RGBLED_H
