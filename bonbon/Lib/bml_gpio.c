
#include "bml_gpio.h"
#include "bml_rcc.h"

#define GPIO_MAX_PIN 15U

GpioStatus_t bmlGpioInit(GpioPort_t *port, unsigned int pin, GpioMode_t mode)
{
    if (bmlRccEnableGpioClock((uint32_t)(port)) != 0)
        return GPIO_ERROR_INVALID_PORT;
    if (pin > GPIO_MAX_PIN)
        return GPIO_ERROR_INVALID_PIN;

    port->MODER.all &= ~(0x3U << (2 * pin));
    port->MODER.all |= ((mode & 0x3U) << (2 * pin));

    port->OTYPER.all &= ~(1U << pin);
    port->OSPEEDR.all &= ~(0x3U << (2 * pin));
    port->PUPDR.all &= ~(0x3U << (2 * pin));

    return GPIO_OK;
}

void bmlGpioWrite(GpioPort_t *port, unsigned int pin, GpioValue_t val)
{
    if (val == GPIO_HIGH)
        port->BSRR.all = (1U << pin);
    else
        port->BSRR.all = (1U << (pin + 16));
}

GpioValue_t bmlGpioRead(GpioPort_t *port, unsigned int pin)
{
    return (port->IDR.all & (1U << pin)) ? GPIO_HIGH : GPIO_LOW;
}


GpioStatus_t bmlGpioInitSimple(GpioPin_t pin, GpioMode_t mode)
{
    if (bmlRccEnableGpioClock((uint32_t)(pin.port)) != 0)
        return GPIO_ERROR_INVALID_PIN;

    return bmlGpioInit(pin.port, pin.pin, mode);
}


void bmlGpioWriteSimple(GpioPin_t pin, GpioValue_t val)
{
    bmlGpioWrite(pin.port, pin.pin, val);
}

GpioValue_t bmlGpioReadSimple(GpioPin_t pin)
{
    return bmlGpioRead(pin.port, pin.pin);
}


GpioStatus_t bmlGpioInitFull(GpioPin_t pin, GpioMode_t mode, GpioPull_t pull)
{
    if (bmlRccEnableGpioClock((uint32_t)(pin.port)) != 0)
        return GPIO_ERROR_INVALID_PIN;

    // MODER
    pin.port->MODER.all &= ~(0x3U << (2 * pin.pin));
    pin.port->MODER.all |= ((mode & 0x3U) << (2 * pin.pin));

    // OTYPER: Push-Pull
    pin.port->OTYPER.all &= ~(1U << pin.pin);

    // SPEED: Low
    pin.port->OSPEEDR.all &= ~(0x3U << (2 * pin.pin));

    // PUPDR
    pin.port->PUPDR.all &= ~(0x3U << (2 * pin.pin));
    pin.port->PUPDR.all |= ((pull & 0x3U) << (2 * pin.pin));

    return GPIO_OK;
}

void bmlGpioToggle(GpioPin_t pin)
{
    if (pin.port->ODR.all & (1U << pin.pin))
        pin.port->BSRR.all = (1U << (pin.pin + 16)); // Reset
    else
        pin.port->BSRR.all = (1U << pin.pin);        // Set
}


GpioStatus_t bmlGpioSetAltFn(GpioPin_t pin, GpioAltFn_t af)
{
    if (pin.pin > 15) return GPIO_ERROR_INVALID_PIN;

    if (pin.pin < 8) {
        pin.port->AFRL &= ~(0xFU << (4 * pin.pin));
        pin.port->AFRL |= ((af & 0xFU) << (4 * pin.pin));
    } else {
        unsigned int shift = 4 * (pin.pin - 8);
        pin.port->AFRH &= ~(0xFU << shift);
        pin.port->AFRH |= ((af & 0xFU) << shift);
    }

    return GPIO_OK;
}

void bmlGpioSet(GpioPin_t pin)
{
    pin.port->BSRR.all = (1U << pin.pin);
}

void bmlGpioClear(GpioPin_t pin)
{
    pin.port->BSRR.all = (1U << (pin.pin + 16));
}
