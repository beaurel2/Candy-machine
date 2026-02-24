
#include "bml_rcc.h"

int bmlRccEnableGpioClock(unsigned int portBase)
{
    switch (portBase) {
        case 0x40020000: Rcc->AHB1ENR.bits.GPIOAEN = 1; break;
        case 0x40020400: Rcc->AHB1ENR.bits.GPIOBEN = 1; break;
        case 0x40020800: Rcc->AHB1ENR.bits.GPIOCEN = 1; break;
        case 0x40020C00: Rcc->AHB1ENR.bits.GPIODEN = 1; break;
        case 0x40021000: Rcc->AHB1ENR.bits.GPIOEEN = 1; break;
        case 0x40021400: Rcc->AHB1ENR.bits.GPIOFEN = 1; break;
        case 0x40021800: Rcc->AHB1ENR.bits.GPIOGEN = 1; break;
        case 0x40021C00: Rcc->AHB1ENR.bits.GPIOHEN = 1; break;
        default: return -1;
    }
    return 0;
}

int bmlRccEnableUart2Clock(void) {
    // Bit 17 im APB1ENR aktiviert USART2
    Rcc->APB1ENR.bits.USART2EN = 1;
    return 0;
}

int bmlRccEnableTim3Clock(void){
  Rcc->APB1ENR.bits.TIM3EN = 1;
  return 0;
}