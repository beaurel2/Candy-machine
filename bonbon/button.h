/*
 * @file button.h
 * @brief Bonbon-Automat State Machine
 * @brief Copyright 2025 Beaurel Ingride Ngaleu
 */


#ifndef BUTTON_H
#define BUTTON_H

#include "Lib/bml_gpio.h"

void Button_Init(void);
int  Button_IsPressed(void);

#endif
