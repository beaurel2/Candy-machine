/**
 * @file bml_systick.h
 * @brief BareMetal SysTick-Modul für den STM32F446RE
 *
 * @defgroup BML_SYSTICK SysTick-Treiber
 * @brief Funktionen zur Initialisierung, Abfrage und Nutzung des SysTick-Timers
 * @{
 */

#ifndef BML_SYSTICK_H
#define BML_SYSTICK_H


#ifndef AHB_FREQ_HZ
#define AHB_FREQ_HZ 16000000U
#endif

#ifndef SYSTICK_MAX_RELOAD
#define SYSTICK_MAX_RELOAD 0xFFFFFFU
#endif


// SysTick-Registerstruktur
typedef union {
    struct {
        unsigned int ENABLE     : 1;
        unsigned int TICKINT    : 1;
        unsigned int CLKSOURCE  : 1;
        unsigned int RESERVED0  : 13;
        unsigned int COUNTFLAG  : 1;
        unsigned int RESERVED1  : 15;
    } bits;
    unsigned int all;
} SysTick_CTRL_t;

typedef struct {
    volatile SysTick_CTRL_t CTRL;
    volatile unsigned int   LOAD;
    volatile unsigned int   VAL;
    volatile const unsigned int CALIB;
} SysTick_t;

#define Systick ((SysTick_t *)0xE000E010)

// Einheitentyp
typedef enum {
    SYSTICK_UNIT_S,
    SYSTICK_UNIT_MS,
    SYSTICK_UNIT_US,
    SYSTICK_UNIT_NS,
    SYSTICK_UNIT_HZ,
    SYSTICK_UNIT_KHZ,
    SYSTICK_UNIT_MHZ
} SystickUnit_t;

// Interrupt-Auswahl
typedef enum {
    SYSTICK_IRQ_DISABLE = 0,
    SYSTICK_IRQ_ENABLE  = 1
} SystickIrq_t;

// Rückgabecodes
typedef enum {
    SYSTICK_OK = 0,
    SYSTICK_ERROR_INVALID_UNIT = -1,
    SYSTICK_ERROR_OUT_OF_RANGE = -2
} SystickStatus_t;

/**
 * @brief Initialisiert den SysTick-Timer mit Zeit- oder Frequenzeinheit.
 *
 * Diese Funktion wählt automatisch zwischen AHB-Clock und AHB/8,
 * abhängig davon, welche Konfiguration den Tickzähler bestmöglich ausnutzt.
 *
 * Ein erneuter Aufruf der Funktion überschreibt alle Einstellungen – eine separate
 * "Reconfigure"-Funktion ist daher nicht notwendig.
 *
 * @param[in] value        Zeit oder Frequenzwert
 * @param[in] unit         Einheit (z.B. SYSTICK_UNIT_US)
 * @param[in] irq          Interrupt aktivieren/deaktivieren
 * @retval SYSTICK_OK bei Erfolg
 * @retval SYSTICK_ERROR_INVALID_UNIT bei ungültiger Einheit
 * @retval SYSTICK_ERROR_OUT_OF_RANGE wenn Zählerwert nicht darstellbar
 */
SystickStatus_t bmlSystickInit(unsigned int value, SystickUnit_t unit, SystickIrq_t irq);

/**
 * @brief Liest das COUNTFLAG-Bit und löscht es durch den Lesezugriff.
 * @retval 1 wenn der Timer seit dem letzten Abfragen abgelaufen ist, sonst 0.
 */
int bmlSystickGetCountFlag(void);

/**
 * @brief Liest den aktuellen SysTick-Zählerwert.
 * @return Aktueller Wert im VAL-Register.
 */
static inline unsigned int bmlSystickGetCurrentValue(void) {
    return Systick->VAL;
}

/**
 * @brief Setzt den aktuellen SysTick-Zählerwert.
 * @param value Neuer Wert für das VAL-Register.
 */
static inline void bmlSystickSetCurrentValue(unsigned int value) {
    Systick->VAL = value;
}

/**
 * @brief SysTick-Interrupt-Handler (schwach definiert – kann überschrieben werden).
 *
 * Wird automatisch vom NVIC bei Ablauf des SysTick-Timers aufgerufen,
 * wenn der Interrupt aktiviert wurde. Die Standardimplementierung ist leer
 * und kann vom Anwender überschrieben werden.
 */
void SysTick_Handler(void);

#endif // BML_SYSTICK_H

/** @} */