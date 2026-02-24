/*
 * @file servo.c
 * @brief Bonbon-Automat State Machine
 * @brief Copyright 2025 Beaurel Ingride Ngaleu
 */


#include "servo.h"
#include "Lib/bml_timer3.h"
#include "Lib/bml_systick.h"


#define SERVO_STEP_DELAY 5
#define SERVO_STEPS 100

static void delay_ms(unsigned int ms) {
    for (unsigned int i = 0; i < ms; ++i) {
        while (!bmlSystickGetCountFlag());
    }
}

void servo_init(void) {
    bmlTim3PwmInit();
    bmlTim3SetDutyCycle(TIM3_CH1, (SERVO_POS_MIN + SERVO_POS_MAX) / 2, DUTY_RAW16); 
}

// Bewegung Servo 'von' bis 'zu'
void servo_move_smooth(uint16_t von, uint16_t zu) {
    int delta = (int)zu - (int)von;
    int step = (int)delta / SERVO_STEPS;
    for (int i = 0; i <= SERVO_STEPS; i++) {
        uint16_t pos = von + (uint16_t)(step * i);
        bmlTim3SetDutyCycle(TIM3_CH1, pos, DUTY_RAW16);
        delay_ms(SERVO_STEP_DELAY);
    }
}
