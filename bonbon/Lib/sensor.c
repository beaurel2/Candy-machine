/*
 * @file sensor.c
 * @brief Bonbon-Automat State Machine
 * @brief Copyright 2025 Beaurel Ingride Ngaleu
 */

#include "sensor.h"
#include <stdint.h>


//###### MAKRO für ADC-Wandler #######
#define ADC_THRESHOLD_LOW 1800 // muss in des gelesenen Wertes in Funktion sensor_read_adc()

#define RCC_APB2ENR   (*(volatile uint32_t*)0x40023844)
#define GPIOA_MODER   (*(volatile uint32_t*)0x40020000)
#define ADC1_BASE     0x40012000
#define ADC1_SR       (*(volatile uint32_t*)(ADC1_BASE + 0x00))
#define ADC1_CR2      (*(volatile uint32_t*)(ADC1_BASE + 0x08))
#define ADC1_SMPR2    (*(volatile uint32_t*)(ADC1_BASE + 0x10))
#define ADC1_SQR3     (*(volatile uint32_t*)(ADC1_BASE + 0x34))
#define ADC1_DR       (*(volatile uint32_t*)(ADC1_BASE + 0x4C))

void sensor_init(void) {
    // 1. Enable GPIOA clock
    RCC_APB2ENR |= (1 << 8);     // ADC1 clock enable
    *(volatile uint32_t*)0x40023830 |= (1 << 0); // GPIOAEN in RCC_AHB1ENR

    // 2. Setzt PA1 auf analog mode
    GPIOA_MODER |= (3 << (1 * 2)); // MODER1 = 0b11 (analog)

    // 3. Setzt sample time auf channel 1 (PA1)
    ADC1_SMPR2 |= (7 << 3); // 480 cycles für channel 1
}

uint16_t sensor_read_adc(void) {
    // 1. channel 1 auswählen
    ADC1_SQR3 = 1;

    // 2. ADC einschalten und Wandlung starten (SWSTART)
    ADC1_CR2 |= (1 << 0);  
    ADC1_CR2 |= (1 << 30);

    // 3. Warten bis EOC (End of Conversion)
    while (!(ADC1_SR & (1 << 1))) {}

    // 4. Ergebnis lesen und zurückgeben
    unsigned int value = ADC1_DR & 0xFFFF;
    return (uint16_t)(ADC1_DR & 0xFFFF);

}

bool sensor_is_low(void) {
    return sensor_read_adc() < ADC_THRESHOLD_LOW;
}
