#include "bml_timer3.h"
#include "bml_gpio.h"
#include "bml_rcc.h"



Tim3Status_t bmlTim3InitBase(unsigned int countSpeed, Tim3Unit_t countUnit,
                              unsigned int pwmFreq, Tim3Unit_t pwmUnit)
{
    if (countSpeed == 0 || pwmFreq == 0)
        return TIM3_ERROR_INVALID_DUTY;

    if (bmlRccEnableTim3Clock() != 0)
        return TIM3_ERROR_INVALID_PIN;

    unsigned int countFreqHz = 0;
    unsigned int pwmFreqHz = 0;

    // Zähltakt in Hz umrechnen
    switch(countUnit) {
        case TIM3_UNIT_HZ:   countFreqHz = countSpeed; break;
        case TIM3_UNIT_KHZ:
            if (countSpeed > (UINT32_MAX / 1000)) return TIM3_ERROR_INVALID_DUTY;
            countFreqHz = countSpeed * 1000U; break;
        case TIM3_UNIT_MHZ:
            if (countSpeed > (UINT32_MAX / 1000000)) return TIM3_ERROR_INVALID_DUTY;
            countFreqHz = countSpeed * 1000000U; break;
        case TIM3_UNIT_US:
            if (countSpeed == 0 || countSpeed > 1000000) return TIM3_ERROR_INVALID_DUTY;
            countFreqHz = 1000000U / countSpeed; break;
        case TIM3_UNIT_MS:
            if (countSpeed == 0 || countSpeed > 1000) return TIM3_ERROR_INVALID_DUTY;
            countFreqHz = 1000U / countSpeed; break;
        case TIM3_UNIT_NS:
            if (countSpeed == 0 || countSpeed > 1000000000U) return TIM3_ERROR_INVALID_DUTY;
            countFreqHz = 1000000000U / countSpeed; break;
        case TIM3_UNIT_S:
            if (countSpeed > 1) return TIM3_ERROR_INVALID_DUTY;
            countFreqHz = 1; break;
        default:
            return TIM3_ERROR_INVALID_DUTY;
    }

    // PWM-Frequenz in Hz
    switch(pwmUnit) {
        case TIM3_UNIT_HZ:   pwmFreqHz = pwmFreq; break;
        case TIM3_UNIT_KHZ:
            if (pwmFreq > (UINT32_MAX / 1000)) return TIM3_ERROR_INVALID_DUTY;
            pwmFreqHz = pwmFreq * 1000U; break;
        case TIM3_UNIT_MHZ:
            if (pwmFreq > (UINT32_MAX / 1000000)) return TIM3_ERROR_INVALID_DUTY;
            pwmFreqHz = pwmFreq * 1000000U; break;
        case TIM3_UNIT_US:
            if (pwmFreq == 0 || pwmFreq > 1000000U) return TIM3_ERROR_INVALID_DUTY;
            pwmFreqHz = 1000000U / pwmFreq; break;
        case TIM3_UNIT_MS:
            if (pwmFreq == 0 || pwmFreq > 1000U) return TIM3_ERROR_INVALID_DUTY;
            pwmFreqHz = 1000U / pwmFreq; break;
        case TIM3_UNIT_NS:
            if (pwmFreq == 0 || pwmFreq > 1000000000U) return TIM3_ERROR_INVALID_DUTY;
            pwmFreqHz = 1000000000U / pwmFreq; break;
        case TIM3_UNIT_S:
            if (pwmFreq > 1) return TIM3_ERROR_INVALID_DUTY;
            pwmFreqHz = 1; break;
        default:
            return TIM3_ERROR_INVALID_DUTY;
    }

    if (countFreqHz == 0 || pwmFreqHz == 0 || countFreqHz > AHB_FREQ_HZ)
        return TIM3_ERROR_INVALID_DUTY;

    // Vor Berechnung prüfen: passt ARR?
    if (pwmFreqHz > countFreqHz) // ergibt ARR < 1 → ungültig
        return TIM3_ERROR_INVALID_DUTY;

    unsigned int arr = countFreqHz / pwmFreqHz;
    if (arr == 0 || arr > 0xFFFF)
        return TIM3_ERROR_INVALID_DUTY;

    // PSC berechnen
    unsigned int psc = AHB_FREQ_HZ / countFreqHz;
    if (psc == 0) psc = 1;
    else psc -= 1;

    if (psc > 0xFFFF)
        return TIM3_ERROR_INVALID_DUTY;

    // Register setzen
    TIM3->PSC.bits.PSC = psc;
    TIM3->ARR.bits.ARR = arr;
    TIM3->EGR.bits.UG = 1;
    TIM3->CR1.bits.CEN = 1;

    return TIM3_OK;
}



Tim3Status_t bmlTim3InitChannel(GpioPin_t pin, uint16_t start_duty_percent, Tim3Polarity_e polarity)
{
    if (start_duty_percent > 100)
        return TIM3_ERROR_INVALID_DUTY;

    bmlGpioInitSimple(pin, GPIO_MODE_ALTFN);

    unsigned int ccr_val = (start_duty_percent * TIM3->ARR.bits.ARR) / 100;

    if (pin.port == GpioA && pin.pin == PIN6) {
        bmlGpioSetAltFn(pin, GPIO_AF_TIM3);
        TIM3->CCMR1.outBits.OC1M = 6;
        TIM3->CCER.bits.CC1P = (polarity == TIM3_POLARITY_LOW);
        TIM3->CCER.bits.CC1E = 1;
        TIM3->CCR1.bits.CCR = ccr_val;
    } else if (pin.port == GpioA && pin.pin == PIN7) {
        bmlGpioSetAltFn(pin, GPIO_AF_TIM3);
        TIM3->CCMR1.outBits.OC2M = 6;
        //TIM3->CCMR1.outBits.OC2PE = 1;
        TIM3->CCER.bits.CC2P = (polarity == TIM3_POLARITY_LOW);
        TIM3->CCER.bits.CC2E = 1;
        TIM3->CCR2.bits.CCR = ccr_val;
    } else if (pin.port == GpioC && pin.pin == PIN8) {
        bmlGpioSetAltFn(pin, GPIO_AF_TIM3);
        TIM3->CCMR2.outBits.OC3M = 6;
        //TIM3->CCMR2.outBits.OC3PE = 1;
        TIM3->CCER.bits.CC3P = (polarity == TIM3_POLARITY_LOW);
        TIM3->CCER.bits.CC3E = 1;
        TIM3->CCR3.bits.CCR = ccr_val;
    } else if (pin.port == GpioC && pin.pin == PIN9) {
        bmlGpioSetAltFn(pin, GPIO_AF_TIM3);
        TIM3->CCMR2.outBits.OC4M = 6;
        //TIM3->CCMR2.outBits.OC4PE = 1;
        TIM3->CCER.bits.CC4P = (polarity == TIM3_POLARITY_LOW);
        TIM3->CCER.bits.CC4E = 1;
        TIM3->CCR4.bits.CCR = ccr_val;
    } else {
        return TIM3_ERROR_INVALID_PIN;
    }

    return TIM3_OK;
}


Tim3Status_t  bmlTim3SetDutyCycle(Tim3Channel_e ch, unsigned int value, DutyMode_e mode)
{
    unsigned int arr = TIM3->ARR.bits.ARR;
    if (arr == 0)
        return TIM3_ERROR_INVALID_DUTY;

    unsigned int ccr_value = 0;

    switch(mode) {
        case DUTY_PERCENT:
            if (value > 100) return TIM3_ERROR_INVALID_DUTY;
            ccr_value = (value * arr) / 100;
            break;
        case DUTY_PROMILLE:
            if (value > 1000) return TIM3_ERROR_INVALID_DUTY;
            ccr_value = (value * arr) / 1000;
            break;
        case DUTY_RAW16:
            if (value > arr) return TIM3_ERROR_INVALID_DUTY;
            ccr_value = value;
            break;
        case DUTY_BASE255:
            if (value > 255) return TIM3_ERROR_INVALID_DUTY;
            ccr_value = (value * arr) / 255;
            break;
        case DUTY_SERVO_PERCENT:
            if (value > 100) return TIM3_ERROR_INVALID_DUTY;
            ccr_value = arr/20 + ((value * arr/20) / 100);
            break;
        case DUTY_SERVO_BASE180:
            if (value > 180) return TIM3_ERROR_INVALID_DUTY;
            ccr_value = arr/20 + ((value * arr/20) / 180);
            break;
    

        default:
            return TIM3_ERROR_INVALID_DUTY;
    }

    switch(ch) {
        case TIM3_CH1: TIM3->CCR1.all = ccr_value; break;
        case TIM3_CH2: TIM3->CCR2.all = ccr_value; break;
        case TIM3_CH3: TIM3->CCR3.bits.CCR = ccr_value; break;
        case TIM3_CH4: TIM3->CCR4.bits.CCR = ccr_value; break;
        default: return TIM3_ERROR_INVALID_CHANNEL;
    }

    return TIM3_OK;
}


Tim3Status_t bmlTim3SetTon(Tim3Channel_e ch, uint32_t duration, Tim3Unit_t unit)
{
    if (duration == 0)
        return TIM3_ERROR_INVALID_DUTY;

    uint32_t psc = TIM3->PSC.bits.PSC + 1;
    uint32_t arr = TIM3->ARR.bits.ARR;
    uint32_t timerClkHz = AHB_FREQ_HZ / psc;
    uint32_t ticks = 0;

    switch(unit)
    {
        case TIM3_UNIT_US:
            if (duration > (UINT32_MAX / timerClkHz))
                return TIM3_ERROR_INVALID_DUTY;
            ticks = (duration * timerClkHz) / 1000000U;
            break;

        case TIM3_UNIT_MS:
            if (duration > (UINT32_MAX / timerClkHz / 1000U))
                return TIM3_ERROR_INVALID_DUTY;
            ticks = (duration * timerClkHz) / 1000U;
            break;

        default:
            return TIM3_ERROR_INVALID_DUTY; // Nur us und ms zulässig
    }

    if (ticks > arr)
        ticks = arr;

    switch(ch)
    {
        case TIM3_CH1: TIM3->CCR1.bits.CCR = ticks; break;
        case TIM3_CH2: TIM3->CCR2.bits.CCR = ticks; break;
        case TIM3_CH3: TIM3->CCR3.bits.CCR = ticks; break;
        case TIM3_CH4: TIM3->CCR4.bits.CCR = ticks; break;
        default: return TIM3_ERROR_INVALID_CHANNEL;
    }

    return TIM3_OK;
}

Tim3Status_t bmlTim3PwmInit(void) {
    Tim3Status_t status;

    // 1. Init base timer: 1 MHz counter, 50 Hz PWM frequency
    status = bmlTim3InitBase(1, TIM3_UNIT_MHZ, 50, TIM3_UNIT_HZ);
    if (status != TIM3_OK) return status;

    // 2. Init each channel with appropriate GPIOs
    // CH1 – PA6 – Servo
    status = bmlTim3InitChannel(PA6, 5, TIM3_POLARITY_HIGH);
    if (status != TIM3_OK) return status;

    // CH2 – PA7 – RGB RED
    status = bmlTim3InitChannel(PA7, 0, TIM3_POLARITY_HIGH);
    if (status != TIM3_OK) return status;

    // CH3 – PB0 – RGB GREEN
    status = bmlTim3InitChannel(PB0, 0, TIM3_POLARITY_HIGH);
    if (status != TIM3_OK) return status;

    // CH4 – PB1 – RGB BLUE
    status = bmlTim3InitChannel(PB1, 0, TIM3_POLARITY_HIGH);
    if (status != TIM3_OK) return status;

    return TIM3_OK;
}