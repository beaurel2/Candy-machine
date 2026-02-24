/*
 * @file sensor.h
 * @brief Bonbon-Automat State Machine
 * @brief Copyright 2025 Beaurel Ingride Ngaleu
 */


#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>
#include <stdbool.h>

// Initializes ADC (if needed)
void sensor_init(void);

// Returns true if fill level is LOW
bool sensor_is_low(void);

// Returns raw ADC value (0–4095)
uint16_t sensor_read_adc(void);

#endif // SENSOR_H
