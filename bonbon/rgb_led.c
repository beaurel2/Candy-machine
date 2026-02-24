/*
 * @file rgb_led.c
 * @brief Bonbon-Automat State Machine
 * @brief Copyright 2025 Beaurel Ingride Ngaleu
 */


#include "rgb_led.h"
#include "Lib/bml_timer3.h"

void rgb_led_init(void) {
    bmlTim3PwmInit();
}

void rgb_led_state_blau(void){
    bmlTim3SetDutyCycle(TIM3_CH2, 0, DUTY_PERCENT); // RED
    bmlTim3SetDutyCycle(TIM3_CH3, 0, DUTY_PERCENT); // GREEN
    bmlTim3SetDutyCycle(TIM3_CH4, 100, DUTY_PERCENT); // BLUE
}

void rgb_led_state_gruen(void){
    bmlTim3SetDutyCycle(TIM3_CH2, 0, DUTY_PERCENT); // RED
    bmlTim3SetDutyCycle(TIM3_CH3, 100, DUTY_PERCENT); // GREEN
    bmlTim3SetDutyCycle(TIM3_CH4, 0, DUTY_PERCENT); // BLUE
}

void rgb_led_state_rot(void){
    bmlTim3SetDutyCycle(TIM3_CH2, 100, DUTY_PERCENT); // RED
    bmlTim3SetDutyCycle(TIM3_CH3, 0, DUTY_PERCENT); // GREEN
    bmlTim3SetDutyCycle(TIM3_CH4, 0, DUTY_PERCENT); // BLUE
}
