/*
 * @file main.c
 * @brief Bonbon-Automat State Machine
 * @brief Copyright 2025 Beaurel Ingride Ngaleu
 */

#include "Lib/bml_rcc.h"
#include "Lib/bml_gpio.h"
#include "Lib/bml_systick.h"
#include "Lib/bml_timer3.h"

#include "servo.h"
#include "rgb_led.h"
#include "sensor.h"

#include <stdbool.h>
#include <stdint.h>

// ==== MACRO ==== //
#define MAX_DISPENSE_LOW 3

#define BUTTON_PORT GpioC
#define BUTTON_PIN 13
GpioPin_t buttonPin = { BUTTON_PORT, BUTTON_PIN };


// ==== ZUSTAND MASCHINE ==== //
typedef enum {
    STATE_IDLE,
    STATE_BEWEGUNG,
    STATE_STOCK_LOW,
    STATE_BLOCKED
} SystemState;

SystemState Aktuelle_State = STATE_IDLE;  // Aktueller Zustand zuerst mit mit STATE_IDLE initialisieren
uint8_t dispenseCounter = 0;     // Counter für Verteilung

static void delay_ms(unsigned int ms) {
    for (unsigned int i = 0; i < ms; ++i) {
        while (!bmlSystickGetCountFlag());
    }
}

bool isButtonPressed(void) {
    return bmlGpioReadSimple(buttonPin) == GPIO_LOW; // Der Wert von PC13 wird gelesen
}

// ==== MAIN ==== //
int main(void) {
    // Core init
    bmlRccEnableGpioClock((uint32_t)BUTTON_PORT);
    bmlGpioInitFull(buttonPin, GPIO_MODE_INPUT, GPIO_PULLUP); // Button (low-aktiv) als INPUT setzen
    bmlSystickInit(1, SYSTICK_UNIT_MS, SYSTICK_IRQ_DISABLE);  

    // Aufruf der Init jeder Funktion aus der Bibliothek
    servo_init();
    rgb_led_init();
    sensor_init();

    // Um die PWM-Kanal mit gewünschtem Duty-Cycle und Polarität zu initialisieren
    // TIM3_POLARITY_LOW = 1;
    bmlTim3InitChannel(PA7, 0, TIM3_POLARITY_LOW);
    bmlTim3InitChannel(PC8, 0, TIM3_POLARITY_LOW);
    bmlTim3InitChannel(PC9, 0, TIM3_POLARITY_LOW);

    bmlTim3SetDutyCycle(TIM3_CH2, 2 , DUTY_PERCENT); 
    bmlTim3SetDutyCycle(TIM3_CH3, 2 , DUTY_PERCENT);
    bmlTim3SetDutyCycle(TIM3_CH4, 2 , DUTY_PERCENT);

    bool vorherige_Button = false;

    while (1) {
        bool sensor_low = sensor_is_low();
        bool button = isButtonPressed();

        switch (Aktuelle_State) {
            case STATE_IDLE:
                if (sensor_low) {
                    Aktuelle_State = STATE_STOCK_LOW;
                    break;
                }
                rgb_led_state_gruen();

                // Button press event (falling edge)
                if (button && !vorherige_Button) {
                    Aktuelle_State = STATE_BEWEGUNG;
                }
                break;

            case STATE_STOCK_LOW:
                  rgb_led_state_rot();

                if (!sensor_low) {
                    dispenseCounter = 0;
                    Aktuelle_State = STATE_IDLE;
                } else if (dispenseCounter >= MAX_DISPENSE_LOW) {
                    Aktuelle_State = STATE_BLOCKED;
                } else if (button && !vorherige_Button) {
                    Aktuelle_State = STATE_BEWEGUNG;
                }
                break;

            case STATE_BEWEGUNG:
                rgb_led_state_blau();

                // Bewegung nach vorne und dann zurück
                servo_move_smooth(SERVO_POS_MIN, SERVO_POS_MAX);
                servo_move_smooth(SERVO_POS_MAX, SERVO_POS_MIN);

                // Warten Sie, bis der Taster losgelassen wird,
                // um eine Mehrfachausgabe zu vermeiden
                while (isButtonPressed());

                // wenn sensor_low ist, count dispense
                if (sensor_low) {   
                    dispenseCounter++;
                    Aktuelle_State = STATE_STOCK_LOW;
                } else {
                    Aktuelle_State = STATE_IDLE;
                }
                break;

            case STATE_BLOCKED:  
                rgb_led_state_rot();
                if (!sensor_low) {
                    dispenseCounter = 0;
                    Aktuelle_State = STATE_IDLE;
                }
                break;
        }

        vorherige_Button = button;
        delay_ms(5); 
    }
}
