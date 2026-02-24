#include "bml_nvic.h"

void bmlNvicEnableIrq(unsigned int irq) {
    NVIC_ISER0[irq >> 5] = (1 << (irq & 0x1F));
}

void bmlNvicDisableIrq(unsigned int irq) {
    NVIC_ICER0[irq >> 5] = (1 << (irq & 0x1F));
}

void bmlNvicSetPriority(unsigned int irq, unsigned char priority) {
    NVIC_IPR_BASE[irq] = priority << 4; // nur obere 4 Bit wirksam
}

void bmlNvicSetPriorityGrouping(unsigned int group) {
    SCB_AIRCR = SCB_AIRCR_VECTKEY | (SCB_AIRCR & ~SCB_AIRCR_PRIGROUP_MASK) | (group << 8);
}

void bmlCpuSetBasePri(unsigned char priority) {
    __asm volatile ("msr BASEPRI, %0" :: "r"(priority));
}

void bmlCpuSetPriMask(unsigned char value) {
    if (value)
        __asm volatile ("cpsid i"); // disable IRQ
    else
        __asm volatile ("cpsie i"); // enable IRQ
}
