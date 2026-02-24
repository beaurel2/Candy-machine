/**
 * @file bml_gpio.h
 * @brief BareMetal GPIO-Modul für den STM32F446RE
 *
 * @defgroup BML_GPIO GPIO-Treiber
 * @brief Funktionen zur Initialisierung, Steuerung und Abfrage digitaler Ein-/Ausgänge
 * @{
 */


#ifndef BML_GPIO_H
#define BML_GPIO_H

#include <stdint.h>

#define GPIOA_BASE (0x40020000UL)
#define GPIOB_BASE (0x40020400UL)
#define GPIOC_BASE (0x40020800UL)

typedef enum {
    GPIO_MODE_INPUT  = 0x0,
    GPIO_MODE_OUTPUT = 0x1,
    GPIO_MODE_ALTFN  = 0x2,
    GPIO_MODE_ANALOG = 0x3
} GpioMode_t;

typedef enum {
    GPIO_OUTPUT_PUSHPULL  = 0x0,
    GPIO_OUTPUT_OPENDRAIN = 0x1
} GpioOutputType_t;

typedef enum {
    GPIO_SPEED_LOW     = 0x0,
    GPIO_SPEED_MEDIUM  = 0x1,
    GPIO_SPEED_FAST    = 0x2,
    GPIO_SPEED_HIGH    = 0x3
} GpioSpeed_t;

typedef enum {
    GPIO_LOW  = 0,
    GPIO_HIGH = 1
} GpioValue_t;

typedef enum {
    GPIO_OK = 0,
    GPIO_ERROR_INVALID_PIN = -1,
    GPIO_ERROR_INVALID_PORT= -2
} GpioStatus_t;

// ---------- Bitfelder ----------

typedef union {
    struct {
        unsigned int PIN0  : 2;
        unsigned int PIN1  : 2;
        unsigned int PIN2  : 2;
        unsigned int PIN3  : 2;
        unsigned int PIN4  : 2;
        unsigned int PIN5  : 2;
        unsigned int PIN6  : 2;
        unsigned int PIN7  : 2;
        unsigned int PIN8  : 2;
        unsigned int PIN9  : 2;
        unsigned int PIN10 : 2;
        unsigned int PIN11 : 2;
        unsigned int PIN12 : 2;
        unsigned int PIN13 : 2;
        unsigned int PIN14 : 2;
        unsigned int PIN15 : 2;
    } bits;
    unsigned int all;
} Gpio2BitReg_t;

typedef union {
    struct {
        unsigned int PIN0  : 1;
        unsigned int PIN1  : 1;
        unsigned int PIN2  : 1;
        unsigned int PIN3  : 1;
        unsigned int PIN4  : 1;
        unsigned int PIN5  : 1;
        unsigned int PIN6  : 1;
        unsigned int PIN7  : 1;
        unsigned int PIN8  : 1;
        unsigned int PIN9  : 1;
        unsigned int PIN10 : 1;
        unsigned int PIN11 : 1;
        unsigned int PIN12 : 1;
        unsigned int PIN13 : 1;
        unsigned int PIN14 : 1;
        unsigned int PIN15 : 1;
        unsigned int RESERVED : 16;
    } bits;
    unsigned int all;
} Gpio16BitReg_t;

typedef union {
    struct {
        unsigned int SET0  : 1;
        unsigned int SET1  : 1;
        unsigned int SET2  : 1;
        unsigned int SET3  : 1;
        unsigned int SET4  : 1;
        unsigned int SET5  : 1;
        unsigned int SET6  : 1;
        unsigned int SET7  : 1;
        unsigned int SET8  : 1;
        unsigned int SET9  : 1;
        unsigned int SET10 : 1;
        unsigned int SET11 : 1;
        unsigned int SET12 : 1;
        unsigned int SET13 : 1;
        unsigned int SET14 : 1;
        unsigned int SET15 : 1;
        unsigned int CLR0  : 1;
        unsigned int CLR1  : 1;
        unsigned int CLR2  : 1;
        unsigned int CLR3  : 1;
        unsigned int CLR4  : 1;
        unsigned int CLR5  : 1;
        unsigned int CLR6  : 1;
        unsigned int CLR7  : 1;
        unsigned int CLR8  : 1;
        unsigned int CLR9  : 1;
        unsigned int CLR10 : 1;
        unsigned int CLR11 : 1;
        unsigned int CLR12 : 1;
        unsigned int CLR13 : 1;
        unsigned int CLR14 : 1;
        unsigned int CLR15 : 1;
    } bits;
    unsigned int all;
} GpioBSRR_t;

typedef union {
    struct {
        unsigned int PIN0  : 1;
        unsigned int PIN1  : 1;
        unsigned int PIN2  : 1;
        unsigned int PIN3  : 1;
        unsigned int PIN4  : 1;
        unsigned int PIN5  : 1;
        unsigned int PIN6  : 1;
        unsigned int PIN7  : 1;
        unsigned int PIN8  : 1;
        unsigned int PIN9  : 1;
        unsigned int PIN10 : 1;
        unsigned int PIN11 : 1;
        unsigned int PIN12 : 1;
        unsigned int PIN13 : 1;
        unsigned int PIN14 : 1;
        unsigned int PIN15 : 1;
        unsigned int LCKK  : 1;
        unsigned int RESERVED : 15;
    } bits;
    unsigned int all;
} GpioLCKR_t;

// ---------- Hauptstruktur ----------

typedef struct {
    volatile Gpio2BitReg_t  MODER;
    volatile Gpio16BitReg_t OTYPER;
    volatile Gpio2BitReg_t  OSPEEDR;
    volatile Gpio2BitReg_t  PUPDR;
    volatile Gpio16BitReg_t IDR;
    volatile Gpio16BitReg_t ODR;
    volatile GpioBSRR_t     BSRR;
    volatile GpioLCKR_t     LCKR;
    volatile uint32_t       AFRL;
    volatile uint32_t       AFRH;
} GpioPort_t;

#define GpioA ((GpioPort_t *) GPIOA_BASE)
#define GpioB ((GpioPort_t *) GPIOB_BASE)
#define GpioC ((GpioPort_t *) GPIOC_BASE)


typedef enum {
    GPIO_NOPULL = 0x0,
    GPIO_PULLUP = 0x1,
    GPIO_PULLDOWN = 0x2
} GpioPull_t;



typedef enum {
    GPIO_AF_SYSTEM     = 0,  // z. B. MCO, RTC, WKUP
    GPIO_AF_TIM1       = 1,
    GPIO_AF_TIM2       = 1,
    GPIO_AF_TIM3       = 2,
    GPIO_AF_TIM4       = 2,
    GPIO_AF_TIM5       = 2,
    GPIO_AF_TIM8       = 3,
    GPIO_AF_TIM9       = 3,
    GPIO_AF_TIM10      = 3,
    GPIO_AF_TIM11      = 3,
    GPIO_AF_I2C1       = 4,
    GPIO_AF_I2C2       = 4,
    GPIO_AF_I2C3       = 4,
    GPIO_AF_SPI1       = 5,
    GPIO_AF_SPI2       = 5,
    GPIO_AF_SPI3       = 6,
    GPIO_AF_USART1     = 7,
    GPIO_AF_USART2     = 7,
    GPIO_AF_USART3     = 7,
    GPIO_AF_UART4      = 8,
    GPIO_AF_UART5      = 8,
    GPIO_AF_USART6     = 8,
    GPIO_AF_CAN1       = 9,
    GPIO_AF_CAN2       = 9,
    GPIO_AF_TIM12      = 9,
    GPIO_AF_TIM13      = 9,
    GPIO_AF_TIM14      = 9,
    GPIO_AF_OTG_FS     = 10,
    GPIO_AF_OTG_HS     = 10,
    GPIO_AF_ETH        = 11,
    GPIO_AF_FMC        = 12,
    GPIO_AF_SDIO       = 12,
    GPIO_AF_DCMI       = 13,
    GPIO_AF_LTDC       = 14,
    GPIO_AF_EVENTOUT   = 15
} GpioAltFn_t;


// ---------- Pin-Enum ----------

typedef enum {
    PIN0  = 0,
    PIN1  = 1,
    PIN2  = 2,
    PIN3  = 3,
    PIN4  = 4,
    PIN5  = 5,
    PIN6  = 6,
    PIN7  = 7,
    PIN8  = 8,
    PIN9  = 9,
    PIN10 = 10,
    PIN11 = 11,
    PIN12 = 12,
    PIN13 = 13,
    PIN14 = 14,
    PIN15 = 15
} GpioPinNumber_t;

// ---------- Kombinierte Port-Pin-Definition ----------

typedef struct {
    GpioPort_t *port;
    GpioPinNumber_t pin;
} GpioPin_t;

// Port A
#define PA0   ((GpioPin_t){ GpioA, PIN0 })
#define PA1   ((GpioPin_t){ GpioA, PIN1 })
#define PA2   ((GpioPin_t){ GpioA, PIN2 })
#define PA3   ((GpioPin_t){ GpioA, PIN3 })
#define PA4   ((GpioPin_t){ GpioA, PIN4 })
#define PA5   ((GpioPin_t){ GpioA, PIN5 })
#define PA6   ((GpioPin_t){ GpioA, PIN6 })
#define PA7   ((GpioPin_t){ GpioA, PIN7 })
#define PA8   ((GpioPin_t){ GpioA, PIN8 })
#define PA9   ((GpioPin_t){ GpioA, PIN9 })
#define PA10  ((GpioPin_t){ GpioA, PIN10 })
#define PA11  ((GpioPin_t){ GpioA, PIN11 })
#define PA12  ((GpioPin_t){ GpioA, PIN12 })
#define PA13  ((GpioPin_t){ GpioA, PIN13 })
#define PA14  ((GpioPin_t){ GpioA, PIN14 })
#define PA15  ((GpioPin_t){ GpioA, PIN15 })

// Port B
#define PB0   ((GpioPin_t){ GpioB, PIN0 })
#define PB1   ((GpioPin_t){ GpioB, PIN1 })
#define PB2   ((GpioPin_t){ GpioB, PIN2 })
#define PB3   ((GpioPin_t){ GpioB, PIN3 })
#define PB4   ((GpioPin_t){ GpioB, PIN4 })
#define PB5   ((GpioPin_t){ GpioB, PIN5 })
#define PB6   ((GpioPin_t){ GpioB, PIN6 })
#define PB7   ((GpioPin_t){ GpioB, PIN7 })
#define PB8   ((GpioPin_t){ GpioB, PIN8 })
#define PB9   ((GpioPin_t){ GpioB, PIN9 })
#define PB10  ((GpioPin_t){ GpioB, PIN10 })
#define PB11  ((GpioPin_t){ GpioB, PIN11 })
#define PB12  ((GpioPin_t){ GpioB, PIN12 })
#define PB13  ((GpioPin_t){ GpioB, PIN13 })
#define PB14  ((GpioPin_t){ GpioB, PIN14 })
#define PB15  ((GpioPin_t){ GpioB, PIN15 })

// Port C
#define PC0   ((GpioPin_t){ GpioC, PIN0 })
#define PC1   ((GpioPin_t){ GpioC, PIN1 })
#define PC2   ((GpioPin_t){ GpioC, PIN2 })
#define PC3   ((GpioPin_t){ GpioC, PIN3 })
#define PC4   ((GpioPin_t){ GpioC, PIN4 })
#define PC5   ((GpioPin_t){ GpioC, PIN5 })
#define PC6   ((GpioPin_t){ GpioC, PIN6 })
#define PC7   ((GpioPin_t){ GpioC, PIN7 })
#define PC8   ((GpioPin_t){ GpioC, PIN8 })
#define PC9   ((GpioPin_t){ GpioC, PIN9 })
#define PC10  ((GpioPin_t){ GpioC, PIN10 })
#define PC11  ((GpioPin_t){ GpioC, PIN11 })
#define PC12  ((GpioPin_t){ GpioC, PIN12 })
#define PC13  ((GpioPin_t){ GpioC, PIN13 })
#define PC14  ((GpioPin_t){ GpioC, PIN14 })
#define PC15  ((GpioPin_t){ GpioC, PIN15 })

// weitere Makros bei Bedarf ...

// ---------- Vereinfachte Init-Funktion ----------

/**
 * @brief Initialisiert einen GPIO-Pin mit Taktfreigabe.
 * @param pin Kombinierter Port+Pin (z.B. PA5)
 * @param mode Modus (Input/Output)
 * @return GPIO_OK bei Erfolg, sonst Fehler
 */

GpioStatus_t bmlGpioSetAltFn(GpioPin_t pin, GpioAltFn_t af);

GpioStatus_t bmlGpioInitSimple(GpioPin_t pin, GpioMode_t mode);



// ---------- API ----------

/**
 * @brief Initialisiert einen GPIO-Pin mit einfacher Port-/Pin-Angabe.
 *
 * Diese Funktion konfiguriert einen GPIO-Pin für den gewünschten Modus.
 * Sie setzt nur das MODER-Register, keine Pull-ups oder -downs.
 *
 * @param[in] port Zeiger auf den gewünschten GPIO-Port (z.B. GpioA).
 * @param[in] pin  Pinnummer (0–15).
 * @param[in] mode Gewünschter Modus (z.B. GPIO_MODE_OUTPUT).
 *
 * @retval GPIO_OK bei Erfolg
 * @retval GPIO_ERROR_INVALID_PIN bei ungültigem Pin oder Port
 *
 * @code
 * bmlRccEnableGpioClock((uint32_t)GpioA);
 * bmlGpioInit(GpioA, 5, GPIO_MODE_OUTPUT);
 * @endcode
 */
GpioStatus_t bmlGpioInit(GpioPort_t *port, unsigned int pin, GpioMode_t mode);

/**
 * @brief Schreibt einen logischen Wert auf einen GPIO-Pin.
 *
 * @param[in] port Zeiger auf den GPIO-Port.
 * @param[in] pin  Pinnummer (0–15).
 * @param[in] val  Wert (GPIO_LOW oder GPIO_HIGH).
 *
 * @code
 * bmlGpioWrite(GpioA, 5, GPIO_HIGH);
 * @endcode
 */
void bmlGpioWrite(GpioPort_t *port, unsigned int pin, GpioValue_t val);

/**
 * @brief Setzt einen GPIO-Pin auf HIGH.
 *
 * @param[in] pin Struktur mit Port und Pin (z.B. PA5).
 *
 * @code
 * bmlGpioSet(PA5);
 * @endcode
 */
void bmlGpioSet(GpioPin_t pin);

/**
 * @brief Setzt einen GPIO-Pin auf LOW.
 *
 * @param[in] pin Struktur mit Port und Pin (z.B. PB3).
 *
 * @code
 * bmlGpioClear(PB3);
 * @endcode
 */
void bmlGpioClear(GpioPin_t pin);

/**
 * @brief Schreibt einen Wert auf einen GPIO-Pin mit vereinfachtem Zugriff.
 *
 * @param[in] pin Struktur mit Port und Pin (z.B. PC13).
 * @param[in] val Wert (GPIO_LOW oder GPIO_HIGH).
 *
 * @code
 * bmlGpioWriteSimple(PC13, GPIO_LOW);
 * @endcode
 */
void bmlGpioWriteSimple(GpioPin_t pin, GpioValue_t val);

/**
 * @brief Initialisiert einen GPIO-Pin mit voller Konfiguration.
 *
 * Diese Funktion konfiguriert den Pin-Modus sowie Pull-up/Pull-down-Widerstände.
 * Sie aktiviert auch automatisch den RCC-Takt für den zugehörigen Port.
 *
 * @param[in] pin  Struktur mit Port und Pin (z.B. PD2).
 * @param[in] mode Gewünschter Modus (z.B. GPIO_MODE_OUTPUT).
 * @param[in] pull Pull-Konfiguration (z.B. GPIO_PULL_UP).
 *
 * @retval GPIO_OK bei Erfolg
 * @retval GPIO_ERROR_INVALID_PIN bei ungültiger Portadresse
 *
 * @code
 * bmlGpioInitFull(PD2, GPIO_MODE_INPUT, GPIO_PULL_UP);
 * @endcode
 */
GpioStatus_t bmlGpioInitFull(GpioPin_t pin, GpioMode_t mode, GpioPull_t pull);

/**
 * @brief Wechselt den Zustand eines GPIO-Pins (HIGH auf LOW).
 *
 * @param[in] pin Struktur mit Port und Pin.
 *
 * @code
 * bmlGpioToggle(PA5);
 * @endcode
 */
void bmlGpioToggle(GpioPin_t pin);

/**
 * @brief Liest den logischen Zustand eines GPIO-Pins (vereinfachte Variante).
 *
 * @param[in] pin Struktur mit Port und Pin.
 * @return GPIO_LOW oder GPIO_HIGH.
 *
 * @code
 * if (bmlGpioReadSimple(PB6) == GPIO_HIGH) {
 *     // Taste gedrückt
 * }
 * @endcode
 */
GpioValue_t bmlGpioReadSimple(GpioPin_t pin);

/**
 * @brief Liest den Zustand eines GPIO-Pins über Port-/Pin-Angabe.
 *
 * @param[in] port Zeiger auf GPIO-Port.
 * @param[in] pin  Pinnummer (0–15).
 * @return GPIO_LOW oder GPIO_HIGH.
 *
 * @code
 * if (bmlGpioRead(GpioC, 13) == GPIO_LOW) {
 *     // LED aus
 * }
 * @endcode
 */
GpioValue_t bmlGpioRead(GpioPort_t *port, unsigned int pin);


#endif // BML_GPIO_H


/** @} */
