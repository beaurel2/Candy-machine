#include "bml_systick.h"

#define AHB_FREQ_HZ 16000000U
#define SYSTICK_MAX_RELOAD 0xFFFFFFU

SystickStatus_t bmlSystickInit(unsigned int value, SystickUnit_t unit, SystickIrq_t irq)
{
    unsigned int ticksAHB = 0;
    unsigned int ticksAHBdiv8 = 0;

    switch (unit) {
        case SYSTICK_UNIT_S:
            ticksAHB      = value * AHB_FREQ_HZ;
            break;
        case SYSTICK_UNIT_MS:
            ticksAHB      = value * (AHB_FREQ_HZ / 1000U);
            break;
        case SYSTICK_UNIT_US:
            ticksAHB      = value * (AHB_FREQ_HZ / 1000000U);
            break;
        case SYSTICK_UNIT_NS:
            ticksAHB      = (value * (AHB_FREQ_HZ / 1000000U)) / 1000U;
            break;
        case SYSTICK_UNIT_HZ:
            if (value == 0) return SYSTICK_ERROR_OUT_OF_RANGE;
            ticksAHB      = AHB_FREQ_HZ / value;
            break;
        case SYSTICK_UNIT_KHZ:
            if (value == 0) return SYSTICK_ERROR_OUT_OF_RANGE;
            ticksAHB      = AHB_FREQ_HZ / (value * 1000U);
            break;
        case SYSTICK_UNIT_MHZ:
            if (value == 0) return SYSTICK_ERROR_OUT_OF_RANGE;
            ticksAHB      = AHB_FREQ_HZ / (value * 1000000U);
            break;
        default:
            return SYSTICK_ERROR_INVALID_UNIT;
    }
    ticksAHBdiv8  = ticksAHB / 8;
    unsigned int chosenTicks;
    unsigned int clkSource;

    if (ticksAHB <= SYSTICK_MAX_RELOAD && ticksAHB > 0) {
        chosenTicks = ticksAHB;
        clkSource = 1;
    } else if (ticksAHBdiv8 <= SYSTICK_MAX_RELOAD && ticksAHBdiv8 > 0) {
        chosenTicks = ticksAHBdiv8;
        clkSource = 0;
    } else {
        return SYSTICK_ERROR_OUT_OF_RANGE;
    }

    Systick->CTRL.all = 0;
    Systick->LOAD = chosenTicks - 1;
    Systick->VAL = 0;
    Systick->CTRL.bits.CLKSOURCE = clkSource;
    Systick->CTRL.bits.TICKINT = (irq == SYSTICK_IRQ_ENABLE) ? 1 : 0;
    Systick->CTRL.bits.ENABLE = 1;

    return SYSTICK_OK;
}

int bmlSystickGetCountFlag(void)
{
    return Systick->CTRL.bits.COUNTFLAG;
}

__attribute__((weak)) void SysTick_Handler(void)
{
    // Benutzerfunktion – z.B. Zähler erhöhen oder Event setzen
}