/**
 * @file bml_tim3.h
 * @brief BareMetal PWM-Treiber für Timer 3 (TIM3) auf dem STM32F446RE
 *
 * @defgroup BML_TIM3 TIM3 PWM-Treiber
 * @brief Konfiguration und Steuerung von PWM-Kanälen über Timer 3
 * @{
 */

#ifndef BML_TIM3_H
#define BML_TIM3_H

#ifndef AHB_FREQ_HZ
#define AHB_FREQ_HZ 16000000U
#endif

#include "bml_gpio.h"

typedef enum {
    TIM3_OK = 0,
    TIM3_ERROR_INVALID_PIN,
    TIM3_ERROR_INVALID_CHANNEL,
    TIM3_ERROR_INVALID_DUTY,
    TIM3_ERROR_NULL_POINTER
} Tim3Status_t;

typedef enum {
    TIM3_UNIT_S,
    TIM3_UNIT_MS,
    TIM3_UNIT_US,
    TIM3_UNIT_NS,
    TIM3_UNIT_HZ,
    TIM3_UNIT_KHZ,
    TIM3_UNIT_MHZ
} Tim3Unit_t;

// Duty Cycle Format
typedef enum {
    DUTY_PERCENT,
    DUTY_PROMILLE,
    DUTY_RAW16,
    DUTY_BASE255,
    DUTY_SERVO_PERCENT,
    DUTY_SERVO_BASE180
} DutyMode_e;

// PWM-Kanal-Auswahl
typedef enum {
    TIM3_CH1 = 1,
    TIM3_CH2 = 2,
    TIM3_CH3 = 3,
    TIM3_CH4 = 4
} Tim3Channel_e;

typedef enum {
    TIM3_POLARITY_HIGH = 0,
    TIM3_POLARITY_LOW  = 1
} Tim3Polarity_e;

// === Registerstrukturen ===

typedef union {
    unsigned int all;
    struct {
        unsigned int CEN      : 1;
        unsigned int UDIS     : 1;
        unsigned int URS      : 1;
        unsigned int OPM      : 1;
        unsigned int DIR      : 1;
        unsigned int CMS      : 2;
        unsigned int ARPE     : 1;
        unsigned int CKD      : 2;
        unsigned int RESERVED : 22;
    } bits;
} TIM_CR1_t;

typedef union {
    unsigned int all;
    struct {
        unsigned int CCPC     : 1;
        unsigned int RESERVED1: 1;
        unsigned int CCUS     : 1;
        unsigned int CCDS     : 1;
        unsigned int MMS      : 3;
        unsigned int TI1S     : 1;
        unsigned int OIS1     : 1;
        unsigned int OIS1N    : 1;
        unsigned int OIS2     : 1;
        unsigned int OIS2N    : 1;
        unsigned int RESERVED2: 20;
    } bits;
} TIM_CR2_t;

typedef union {
    unsigned int all;
    struct {
        unsigned int SMS      : 3;
        unsigned int OCCS     : 1;
        unsigned int TS       : 3;
        unsigned int MSM      : 1;
        unsigned int ETF      : 4;
        unsigned int ETPS     : 2;
        unsigned int ECE      : 1;
        unsigned int ETP      : 1;
        unsigned int RESERVED : 16;
    } bits;
} TIM_SMCR_t;

typedef union {
    unsigned int all;
    struct {
        unsigned int UIE      : 1;
        unsigned int CC1IE    : 1;
        unsigned int CC2IE    : 1;
        unsigned int RESERVED : 29;
    } bits;
} TIM_DIER_t;

typedef union {
    unsigned int all;
    struct {
        unsigned int UIF      : 1;
        unsigned int CC1IF    : 1;
        unsigned int CC2IF    : 1;
        unsigned int RESERVED : 29;
    } bits;
} TIM_SR_t;

typedef union {
    unsigned int all;
    struct {
        unsigned int UG       : 1;
        unsigned int CC1G     : 1;
        unsigned int CC2G     : 1;
        unsigned int RESERVED : 29;
    } bits;
} TIM_EGR_t;

typedef union {
    unsigned int all;

    struct {
        // Output Compare Mode
        unsigned int CC1S     : 2;
        unsigned int OC1FE    : 1;
        unsigned int OC1PE    : 1;
        unsigned int OC1M     : 3;
        unsigned int OC1CE    : 1;

        unsigned int CC2S     : 2;
        unsigned int OC2FE    : 1;
        unsigned int OC2PE    : 1;
        unsigned int OC2M     : 3;
        unsigned int OC2CE    : 1;

        unsigned int RESERVED : 16;
    } outBits;

    struct {
        // Input Capture Mode
        unsigned int CC1S     : 2;
        unsigned int IC1PSC   : 2;
        unsigned int IC1F     : 4;

        unsigned int CC2S     : 2;
        unsigned int IC2PSC   : 2;
        unsigned int IC2F     : 4;

        unsigned int RESERVED : 16;
    } inBits;
} TIM_CCMR1_t;

typedef union {
    unsigned int all;

    struct {
        // Output Compare Mode für CH3 & CH4
        unsigned int CC3S     : 2;
        unsigned int OC3FE    : 1;
        unsigned int OC3PE    : 1;
        unsigned int OC3M     : 3;
        unsigned int OC3CE    : 1;

        unsigned int CC4S     : 2;
        unsigned int OC4FE    : 1;
        unsigned int OC4PE    : 1;
        unsigned int OC4M     : 3;
        unsigned int OC4CE    : 1;

        unsigned int RESERVED : 16;
    } outBits;

    struct {
        // Input Capture Mode für CH3 & CH4
        unsigned int CC3S     : 2;
        unsigned int IC3PSC   : 2;
        unsigned int IC3F     : 4;

        unsigned int CC4S     : 2;
        unsigned int IC4PSC   : 2;
        unsigned int IC4F     : 4;

        unsigned int RESERVED : 16;
    } inBits;
} TIM_CCMR2_t;


typedef union {
    unsigned int all;
    struct {
        unsigned int CC1E     : 1;
        unsigned int CC1P     : 1;
        unsigned int CC1NE    : 1;
        unsigned int CC1NP    : 1;
        unsigned int CC2E     : 1;
        unsigned int CC2P     : 1;
        unsigned int CC2NE    : 1;
        unsigned int CC2NP    : 1;
        unsigned int CC3E     : 1;
        unsigned int CC3P     : 1;
        unsigned int RESERVED1: 2;
        unsigned int CC4E     : 1;
        unsigned int CC4P     : 1;
        unsigned int RESERVED2: 2;
        unsigned int RESERVED : 16;
    } bits;
} TIM_CCER_t;


typedef union {
    unsigned int all;
    struct {
        unsigned int CNT : 16;
        unsigned int RESERVED : 16;
    } bits;
} TIM_CNT_t;

typedef union {
    unsigned int all;
    struct {
        unsigned int PSC : 16;
        unsigned int RESERVED : 16;
    } bits;
} TIM_PSC_t;

typedef union {
    unsigned int all;
    struct {
        unsigned int ARR : 16;
        unsigned int RESERVED : 16;
    } bits;
} TIM_ARR_t;

typedef union {
    unsigned int all;
    struct {
        unsigned int CCR : 16;
        unsigned int RESERVED : 16;
    } bits;
} TIM_CCR_t;

typedef struct {
    volatile TIM_CR1_t CR1;
    volatile TIM_CR2_t CR2;
    volatile TIM_SMCR_t SMCR;
    volatile TIM_DIER_t DIER;
    volatile TIM_SR_t SR;
    volatile TIM_EGR_t EGR;
    volatile TIM_CCMR1_t CCMR1;
    volatile TIM_CCMR2_t CCMR2;
    volatile TIM_CCER_t CCER;
    volatile TIM_CNT_t CNT;
    volatile TIM_PSC_t PSC;
    volatile TIM_ARR_t ARR;
    volatile unsigned int Reserved;
    volatile TIM_CCR_t CCR1;
    volatile TIM_CCR_t CCR2;
    volatile TIM_CCR_t CCR3;
    volatile TIM_CCR_t CCR4;
} TIM_TypeDef;

#define TIM3 ((TIM_TypeDef*) 0x40000400)

/**
 * @brief Initialisiert den Basisbetrieb von TIM3 für PWM mit gewünschtem Zähltakt und PWM-Frequenz.
 *
 * Diese Funktion setzt Prescaler und Auto-Reload-Wert so, dass der gewünschte PWM-Frequenzwert
 * bei angegebener Timer-Zähltaktgeschwindigkeit erreicht wird. Bei ungültigen Werten oder Überlauf
 * erfolgt eine Fehlerausgabe.
 *
 * @param[in] countSpeed  Taktfrequenz des Timers (z. B. 1 mit Einheit MHz → 1 MHz)
 * @param[in] countUnit   Einheit für countSpeed (z. B. TIM3_UNIT_MHZ)
 * @param[in] pwmFreq     Ziel-PWM-Frequenz (z. B. 1 mit TIM3_UNIT_KHZ → 1 kHz)
 * @param[in] pwmUnit     Einheit für pwmFreq
 * @retval TIM3_OK bei Erfolg
 * @retval TIM3_ERROR_INVALID_DUTY bei Überlauf oder ungültigen Werten
 *
 * @code
 * // Timer mit 1 MHz Takt und 1 kHz PWM-Frequenz initialisieren
 * bmlTim3InitBase(1, TIM3_UNIT_MHZ, 1, TIM3_UNIT_KHZ);
 * @endcode
 *
 */
Tim3Status_t bmlTim3InitBase(unsigned int countSpeed, Tim3Unit_t countUnit, unsigned int pwmFreq, Tim3Unit_t pwmUnit);

/**
 * @brief Initialisiert einen PWM-Kanal (CH1–CH4) mit gewünschtem Duty-Cycle und Polarität.
 *
 * Diese Funktion richtet den GPIO im Alternate-Funktion-Modus ein, aktiviert die PWM-Ausgabe
 * auf dem entsprechenden Kanal und setzt initial den Duty-Cycle.
 *
 * @param[in] pin               PWM-Ausgangspin (z. B. PA6 für CH1)
 * @param[in] start_duty_percent Duty-Cycle in Prozent [0–100]
 * @param[in] polarity          Ausgangspolarität (HIGH oder LOW aktiv)
 * @retval TIM3_OK bei Erfolg
 * @retval TIM3_ERROR_INVALID_PIN oder TIM3_ERROR_INVALID_DUTY
 *
 * @code
 * // PWM-Kanal CH1 (PA6) mit 25 % Duty-Cycle und aktiver High-Polung konfigurieren
 * bmlTim3InitChannel(PA6, 25, TIM3_POLARITY_HIGH);
 * @endcode
 */
Tim3Status_t bmlTim3InitChannel(GpioPin_t pin, uint16_t start_duty_percent, Tim3Polarity_e polarity);

/**
 * @brief Setzt den Duty-Cycle eines Kanals (CH1–CH4).
 *
 * Der Wert wird je nach angegebenem Format (Prozent, Promille, Rohwert etc.) interpretiert
 * und in das zugehörige CCR-Register eingetragen.
 *
 * @param[in] ch     PWM-Kanal (z. B. TIM3_CH1)
 * @param[in] value  Duty-Wert (abhängig vom Format)
 * @param[in] mode   Format (z. B. DUTY_PERCENT, DUTY_RAW16)
 * @retval TIM3_OK bei Erfolg
 * @retval TIM3_ERROR_INVALID_CHANNEL oder TIM3_ERROR_INVALID_DUTY
 *
 * @code
 * // Duty-Cycle auf Kanal 2 auf 75 % setzen
 * bmlTim3SetDutyCycle(TIM3_CH2, 75, DUTY_PERCENT);
 * @endcode
 */
Tim3Status_t bmlTim3SetDutyCycle(Tim3Channel_e ch, unsigned int value, DutyMode_e mode);

/**
 * @brief Setzt die Einschaltzeit (Tonlänge) eines PWM-Kanals.
 *
 * Berechnet intern den CCR-Wert, der der gewünschten Pulsdauer entspricht.
 * ARR bleibt unverändert.
 *
 * @param[in] ch       PWM-Kanal (TIM3_CH1 ... TIM3_CH4)
 * @param[in] duration Dauer der Tonzeit (z. B. 500 mit Einheit us)
 * @param[in] unit     Einheit (nur TIM3_UNIT_US oder TIM3_UNIT_MS erlaubt)
 * @retval TIM3_OK bei Erfolg
 * @retval TIM3_ERROR_INVALID_DUTY oder TIM3_ERROR_INVALID_CHANNEL
 *
 * @code
 * // Tonlänge auf Kanal 4 auf 500 µs setzen
 * bmlTim3SetTon(TIM3_CH4, 500, TIM3_UNIT_US);
 * @endcode
 */
Tim3Status_t bmlTim3SetTon(Tim3Channel_e ch, unsigned int duration, Tim3Unit_t unit);
Tim3Status_t bmlTim3PwmInit(void);

#endif // BML_TIM3_H

/** @} */
