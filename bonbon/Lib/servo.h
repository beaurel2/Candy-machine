/*
 * @file servo.h
 * @brief Bonbon-Automat State Machine
 * @brief Copyright 2025 Beaurel Ingride Ngaleu
 */


#ifndef SERVO_H
#define SERVO_H

#include <stdint.h>

#define SERVO_POS_MIN 1165   // 1.16ms pulse for min (timer tick = 1us)
#define SERVO_POS_MAX 1700   // 1.70ms pulse for max

void servo_init(void);
void servo_move_smooth(uint16_t from, uint16_t to);

#endif
