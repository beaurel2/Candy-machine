#ifndef BML_NVIC_H
#define BML_NVIC_H

#include "bml_irqn.h"
// Basisadressen der NVIC-Register
#define NVIC_ISER0 ((volatile unsigned int *) 0xE000E100)
#define NVIC_ICER0 ((volatile unsigned int *) 0xE000E180)
#define NVIC_ISPR0 ((volatile unsigned int *) 0xE000E200)
#define NVIC_ICPR0 ((volatile unsigned int *) 0xE000E280)
#define NVIC_IPR_BASE ((volatile unsigned char *) 0xE000E400)

#define SCB_BASE     (0xE000ED00UL)
#define SCB_SHPR     ((volatile unsigned char *) (SCB_BASE + 0x18))
#define SCB_AIRCR    (*(volatile unsigned int *)(SCB_BASE + 0x0C))

// Systemsteuerung für Prioritätsgruppen (Voreinstellung: 4 Bits für Präemption, keine Subprio)
#define SCB_AIRCR_PRIGROUP_MASK (0x700)
#define SCB_AIRCR_VECTKEY       (0x5FA << 16)
#define SCB_AIRCR_PRIGROUP_4    (0x3 << 8)

// Bitfeld für ISER0
typedef union {
    struct {
        unsigned int SETENA_0  : 1;
        unsigned int SETENA_1  : 1;
        unsigned int SETENA_2  : 1;
        unsigned int SETENA_3  : 1;
        unsigned int SETENA_4  : 1;
        unsigned int SETENA_5  : 1;
        unsigned int SETENA_6  : 1;
        unsigned int SETENA_7  : 1;
        unsigned int SETENA_8  : 1;
        unsigned int SETENA_9  : 1;
        unsigned int SETENA_10 : 1;
        unsigned int SETENA_11 : 1;
        unsigned int SETENA_12 : 1;
        unsigned int SETENA_13 : 1;
        unsigned int SETENA_14 : 1;
        unsigned int SETENA_15 : 1;
        unsigned int SETENA_16 : 1;
        unsigned int SETENA_17 : 1;
        unsigned int SETENA_18 : 1;
        unsigned int SETENA_19 : 1;
        unsigned int SETENA_20 : 1;
        unsigned int SETENA_21 : 1;
        unsigned int SETENA_22 : 1;
        unsigned int SETENA_23 : 1;
        unsigned int SETENA_24 : 1;
        unsigned int SETENA_25 : 1;
        unsigned int SETENA_26 : 1;
        unsigned int SETENA_27 : 1;
        unsigned int SETENA_28 : 1;
        unsigned int SETENA_29 : 1;
        unsigned int SETENA_30 : 1;
        unsigned int SETENA_31 : 1;
    } bits;
    unsigned int all;
} NvicISER_t;

typedef union {
    struct {
        unsigned int CLRENA_0  : 1;
        unsigned int CLRENA_1  : 1;
        unsigned int CLRENA_2  : 1;
        unsigned int CLRENA_3  : 1;
        unsigned int CLRENA_4  : 1;
        unsigned int CLRENA_5  : 1;
        unsigned int CLRENA_6  : 1;
        unsigned int CLRENA_7  : 1;
        unsigned int CLRENA_8  : 1;
        unsigned int CLRENA_9  : 1;
        unsigned int CLRENA_10 : 1;
        unsigned int CLRENA_11 : 1;
        unsigned int CLRENA_12 : 1;
        unsigned int CLRENA_13 : 1;
        unsigned int CLRENA_14 : 1;
        unsigned int CLRENA_15 : 1;
        unsigned int CLRENA_16 : 1;
        unsigned int CLRENA_17 : 1;
        unsigned int CLRENA_18 : 1;
        unsigned int CLRENA_19 : 1;
        unsigned int CLRENA_20 : 1;
        unsigned int CLRENA_21 : 1;
        unsigned int CLRENA_22 : 1;
        unsigned int CLRENA_23 : 1;
        unsigned int CLRENA_24 : 1;
        unsigned int CLRENA_25 : 1;
        unsigned int CLRENA_26 : 1;
        unsigned int CLRENA_27 : 1;
        unsigned int CLRENA_28 : 1;
        unsigned int CLRENA_29 : 1;
        unsigned int CLRENA_30 : 1;
        unsigned int CLRENA_31 : 1;
    } bits;
    unsigned int all;
} NvicICER_t;

// ---------- API ----------

/**
 * @brief Aktiviert einen Interrupt im NVIC.
 *
 * Setzt das entsprechende Bit im Interrupt Set-Enable Register (ISER).
 *
 * @param irq Interruptnummer (z.B. USART2_IRQn)
 *
 * @code
 * bmlNvicEnableIrq(USART2_IRQn);
 * @endcode
 */
void bmlNvicEnableIrq(unsigned int irq);

/**
 * @brief Deaktiviert einen Interrupt im NVIC.
 *
 * Löscht das entsprechende Bit im Interrupt Clear-Enable Register (ICER).
 *
 * @param irq Interruptnummer (z.B. USART2_IRQn)
 *
 * @code
 * bmlNvicDisableIrq(USART2_IRQn);
 * @endcode
 */
void bmlNvicDisableIrq(unsigned int irq);

/**
 * @brief Setzt die Priorität eines Interrupts.
 *
 * Je höher die Zahl, desto niedriger die Priorität (0 = höchste).
 *
 * @param irq Interruptnummer (z.B. USART2_IRQn)
 * @param priority Priorität (0 bis 15 bei 4 Bit Implementierung)
 *
 * @code
 * bmlNvicSetPriority(USART2_IRQn, 5);
 * @endcode
 */
void bmlNvicSetPriority(unsigned int irq, unsigned char priority);

/**
 * @brief Konfiguriert die Gruppierung von Präemptions- und Subpriorität.
 *
 * Ändert das PRIGROUP-Feld im AIRCR-Register.
 *
 * @param group Gruppencode (z.B. 3 für 4 Bit Präemption, 0 Bit Sub)
 *
 * @code
 * bmlNvicSetPriorityGrouping(3);
 * @endcode
 */
void bmlNvicSetPriorityGrouping(unsigned int group);

/**
 * @brief Setzt das BASEPRI-Register (untere Interruptgrenze).
 *
 * Unterdrückt alle Interrupts mit niedrigerer Priorität als angegeben.
 *
 * @param priority Schwellenwert (0 = keine Maskierung)
 *
 * @code
 * bmlCpuSetBasePri(0x20);  // Unterdrücke alle Prio > 0x20
 * @endcode
 */
void bmlCpuSetBasePri(unsigned char priority);

/**
 * @brief Aktiviert oder deaktiviert global alle IRQs über PRIMASK.
 *
 * @param value 0 = aktivieren (cpsie i), 1 = deaktivieren (cpsid i)
 *
 * @code
 * bmlCpuSetPriMask(1); // Alle IRQs global deaktivieren
 * bmlCpuSetPriMask(0); // IRQs wieder freigeben
 * @endcode
 */
void bmlCpuSetPriMask(unsigned char value);


#endif // BML_NVIC_H
