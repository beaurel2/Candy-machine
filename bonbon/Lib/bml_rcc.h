
/**
 * @file bml_rcc.h
 * @brief BareMetal RCC-Modul für den STM32F446RE
 *
 * @defgroup BML_RCC Taktsteuerung (RCC)
 * @brief Zugriff auf das Reset and Clock Control-System des STM32F446RE
 * @{
 */

#ifndef BML_RCC_H
#define BML_RCC_H

#define RCC_BASE (0x40023800UL)

// Einzelne Bitfeld-Unionen

typedef union {
    struct {
        unsigned int HSION     : 1;
        unsigned int HSIRDY    : 1;
        unsigned int RESERVED0 : 1;
        unsigned int HSITRIM   : 5;
        unsigned int HSICAL    : 8;
        unsigned int HSEON     : 1;
        unsigned int HSERDY    : 1;
        unsigned int HSEBYP    : 1;
        unsigned int CSSON     : 1;
        unsigned int RESERVED1 : 4;
        unsigned int PLLON     : 1;
        unsigned int PLLRDY    : 1;
        unsigned int PLLI2SON  : 1;
        unsigned int PLLI2SRDY : 1;
        unsigned int PLLSAION  : 1;
        unsigned int PLLSAIRDY : 1;
        unsigned int RESERVED2 : 2;
    } bits;
    unsigned int all;
} RccCR_t;

typedef union {
    struct {
        unsigned int PLLM      : 6;
        unsigned int PLLN      : 9;
        unsigned int RESERVED0 : 1;
        unsigned int PLLP      : 2;
        unsigned int RESERVED1 : 4;
        unsigned int PLLSRC    : 1;
        unsigned int RESERVED2 : 1;
        unsigned int PLLQ      : 4;
        unsigned int PLLR      : 3;
        unsigned int RESERVED3 : 1;
    } bits;
    unsigned int all;
} RccPLLCFGR_t;

typedef union {
    struct {
        unsigned int SW        : 2;
        unsigned int SWS       : 2;
        unsigned int HPRE      : 4;
        unsigned int PPRE1     : 3;
        unsigned int PPRE2     : 3;
        unsigned int RTCPRE    : 5;
        unsigned int MCO1      : 2;
        unsigned int I2SSRC    : 1;
        unsigned int MCO1PRE   : 3;
        unsigned int MCO2PRE   : 3;
        unsigned int MCO2      : 2;
        unsigned int RESERVED  : 2;
    } bits;
    unsigned int all;
} RccCFGR_t;

typedef union {
    struct {
        unsigned int LSIRDYF     : 1;
        unsigned int LSERDYF     : 1;
        unsigned int HSIRDYF     : 1;
        unsigned int HSERDYF     : 1;
        unsigned int PLLRDYF     : 1;
        unsigned int PLLI2SRDYF  : 1;
        unsigned int PLLSAIRDYF  : 1;
        unsigned int CSSF        : 1;
        unsigned int LSIRDYIE    : 1;
        unsigned int LSERDYIE    : 1;
        unsigned int HSIRDYIE    : 1;
        unsigned int HSERDYIE    : 1;
        unsigned int PLLRDYIE    : 1;
        unsigned int PLLI2SRDYIE : 1;
        unsigned int PLLSAIRDYIE : 1;
        unsigned int RESERVED0   : 1;
        unsigned int LSIRDYC     : 1;
        unsigned int LSERDYC     : 1;
        unsigned int HSIRDYC     : 1;
        unsigned int HSERDYC     : 1;
        unsigned int PLLRDYC     : 1;
        unsigned int PLLI2SRDYC  : 1;
        unsigned int PLLSAIRDYC  : 1;
        unsigned int CSSC        : 1;
        unsigned int RESERVED1   : 8;
    } bits;
    unsigned int all;
} RccCIR_t;

typedef union {
    struct {
        unsigned int GPIOARST  : 1;
        unsigned int GPIOBRST  : 1;
        unsigned int GPIOCRST  : 1;
        unsigned int GPIODRST  : 1;
        unsigned int GPIOERST  : 1;
        unsigned int GPIOFRST  : 1;
        unsigned int GPIOGRST  : 1;
        unsigned int GPIOHRST  : 1;
        unsigned int RESERVED0 : 2;
        unsigned int DMA1RST   : 1;
        unsigned int DMA2RST   : 1;
        unsigned int RESERVED1 : 8;
        unsigned int CRCRST    : 1;
        unsigned int RESERVED2 : 11;
    } bits;
    unsigned int all;
} RccAHB1RSTR_t;

typedef union {
    struct {
        unsigned int RESERVED0 : 7;
        unsigned int OTGFSRST  : 1;
        unsigned int RESERVED1 : 23;
        unsigned int DCMIRST   : 1;
    } bits;
    unsigned int all;
} RccAHB2RSTR_t;

typedef union {
    struct {
        unsigned int FMCRST   : 1;
        unsigned int QSPIRST  : 1;
        unsigned int RESERVED : 30;
    } bits;
    unsigned int all;
} RccAHB3RSTR_t;

typedef union {
    struct {
        unsigned int TIM2RST     : 1; // Bit 0
        unsigned int TIM3RST     : 1; // Bit 1
        unsigned int TIM4RST     : 1;
        unsigned int TIM5RST     : 1;
        unsigned int TIM6RST     : 1;
        unsigned int TIM7RST     : 1;
        unsigned int TIM12RST    : 1;
        unsigned int TIM13RST    : 1;
        unsigned int TIM14RST    : 1;
        unsigned int RESERVED0   : 2;
        unsigned int WWDGRST     : 1;
        unsigned int RESERVED1   : 2;
        unsigned int SPI2RST     : 1;
        unsigned int SPI3RST     : 1;
        unsigned int SPDIFRXRST  : 1;
        unsigned int USART2RST   : 1;
        unsigned int USART3RST   : 1;
        unsigned int UART4RST    : 1;
        unsigned int UART5RST    : 1;
        unsigned int I2C1RST     : 1;
        unsigned int I2C2RST     : 1;
        unsigned int I2C3RST     : 1;
        unsigned int FMPI2C1RST  : 1;
        unsigned int CAN1RST     : 1;
        unsigned int CAN2RST     : 1;
        unsigned int CECRST      : 1;
        unsigned int PWRRST      : 1;
        unsigned int DACRST      : 1;
        unsigned int RESERVED2   : 2;
    } bits;
    unsigned int all;
} RccAPB1RSTR_t;

typedef union {
    struct {
        unsigned int TIM1RST     : 1;  // Bit 0
        unsigned int TIM8RST     : 1;  // Bit 1
        unsigned int RESERVED0   : 2;
        unsigned int USART1RST   : 1;
        unsigned int USART6RST   : 1;
        unsigned int RESERVED1   : 2;
        unsigned int ADCRST      : 1;
        unsigned int RESERVED2   : 2;
        unsigned int SDIORST     : 1;
        unsigned int SPI1RST     : 1;
        unsigned int SPI4RST     : 1;
        unsigned int SYSCFGRST   : 1;
        unsigned int RESERVED3   : 1;
        unsigned int TIM9RST     : 1;
        unsigned int TIM10RST    : 1;
        unsigned int TIM11RST    : 1;
        unsigned int RESERVED4   : 3;
        unsigned int SAI1RST     : 1;
        unsigned int SAI2RST     : 1;
        unsigned int RESERVED5   : 8;
    } bits;
    unsigned int all;
} RccAPB2RSTR_t;


typedef union {
    struct {
        unsigned int GPIOAEN      : 1;  // Bit 0
        unsigned int GPIOBEN      : 1;  // Bit 1
        unsigned int GPIOCEN      : 1;  // Bit 2
        unsigned int GPIODEN      : 1;  // Bit 3
        unsigned int GPIOEEN      : 1;  // Bit 4
        unsigned int GPIOFEN      : 1;  // Bit 5
        unsigned int GPIOGEN      : 1;  // Bit 6
        unsigned int GPIOHEN      : 1;  // Bit 7
        unsigned int RESERVED0    : 4;  // Bits 8–11
        unsigned int CRCEN        : 1;  // Bit 12
        unsigned int RESERVED1    : 6;  // Bits 13–18
        unsigned int BKPSRAMEN    : 1;  // Bit 19
        unsigned int RESERVED2    : 4;  // Bits 20–23
        unsigned int DMA1EN       : 1;  // Bit 24
        unsigned int DMA2EN       : 1;  // Bit 25
        unsigned int RESERVED3    : 4;  // Bits 26–29
        unsigned int OTGHSEN      : 1;  // Bit 30
        unsigned int OTGHSULPIEN  : 1;  // Bit 31
    } bits;
    unsigned int all;
} RccAHB1ENR_t;

typedef union {
    struct {
        unsigned int RESERVED0 : 26; // Bits 0–25
        unsigned int OTGFSEN   : 1;  // Bit 26
        unsigned int RESERVED1 : 4;  // Bits 27–30
        unsigned int DCMIEN    : 1;  // Bit 31
    } bits;
    unsigned int all;
} RccAHB2ENR_t;

typedef union {
    struct {
        unsigned int FMCEN     : 1;  // Bit 0
        unsigned int QSPIEN    : 1;  // Bit 1
        unsigned int RESERVED  : 30; // Bits 2–31
    } bits;
    unsigned int all;
} RccAHB3ENR_t;


typedef union {
    struct {
        unsigned int TIM2EN     : 1;
        unsigned int TIM3EN     : 1;
        unsigned int TIM4EN     : 1;
        unsigned int TIM5EN     : 1;
        unsigned int TIM6EN     : 1;
        unsigned int TIM7EN     : 1;
        unsigned int TIM12EN    : 1;
        unsigned int TIM13EN    : 1;
        unsigned int TIM14EN    : 1;
        unsigned int RESERVED0  : 2;
        unsigned int WWDGEN     : 1;
        unsigned int RESERVED1  : 2;
        unsigned int SPI2EN     : 1;
        unsigned int SPI3EN     : 1;
        unsigned int SPDIFRXEN  : 1;
        unsigned int USART2EN   : 1;
        unsigned int USART3EN   : 1;
        unsigned int UART4EN    : 1;
        unsigned int UART5EN    : 1;
        unsigned int I2C1EN     : 1;
        unsigned int I2C2EN     : 1;
        unsigned int I2C3EN     : 1;
        unsigned int FMPI2C1EN  : 1;
        unsigned int CAN1EN     : 1;
        unsigned int CAN2EN     : 1;
        unsigned int CECEN      : 1;
        unsigned int PWREN      : 1;
        unsigned int DACEN      : 1;
        unsigned int RESERVED2  : 2;
    } bits;
    unsigned int all;
} RccAPB1ENR_t;

typedef union {
    struct {
        unsigned int TIM1EN     : 1;
        unsigned int TIM8EN     : 1;
        unsigned int RESERVED0  : 2;
        unsigned int USART1EN   : 1;
        unsigned int USART6EN   : 1;
        unsigned int RESERVED1  : 2;
        unsigned int ADC1EN     : 1;
        unsigned int ADC2EN     : 1;
        unsigned int ADC3EN     : 1;
        unsigned int SDIOEN     : 1;
        unsigned int SPI1EN     : 1;
        unsigned int SPI4EN     : 1;
        unsigned int SYSCFGEN   : 1;
        unsigned int RESERVED2  : 1;
        unsigned int TIM9EN     : 1;
        unsigned int TIM10EN    : 1;
        unsigned int TIM11EN    : 1;
        unsigned int RESERVED3  : 3;
        unsigned int SAI2LPEN   : 1;
        unsigned int SAI1LPEN   : 1;
        unsigned int RESERVED   : 8;
    } bits;
    unsigned int all;
} RccAPB2ENR_t;

// Direkte Struktur mit eingebetteten Bitfeld-Unionen

typedef struct {
    volatile RccCR_t CR;                // 0x00
    volatile RccPLLCFGR_t PLLCFGR;      // 0x04
    volatile RccCFGR_t CFGR;            // 0x08
    volatile RccCIR_t CIR;              // 0x0C
    volatile RccAHB1RSTR_t AHB1RSTR;    // 0x10
    volatile RccAHB2RSTR_t AHB2RSTR;    // 0x14
    volatile RccAHB3RSTR_t AHB3RSTR;    // 0x18
    volatile unsigned int RESERVED0;    // 0x1C
    volatile RccAPB1RSTR_t APB1RSTR;    // 0x20
    volatile RccAPB2RSTR_t APB2RSTR;    // 0x24
    volatile unsigned int RESERVED1[2]; // 0x28, 0x2C
    volatile RccAHB1ENR_t AHB1ENR;      // 0x30
    volatile RccAHB2ENR_t AHB2ENR;      // 0x34
    volatile RccAHB3ENR_t AHB3ENR;      // 0x38
    volatile unsigned int RESERVED2;    // 0x3C
    volatile RccAPB1ENR_t APB1ENR;      // 0x40
    volatile RccAPB2ENR_t APB2ENR;      // 0x44
    volatile unsigned int RESERVED3[2]; // 0x48, 0x4C
 //TODO: Weitere Bitfelder definieren
    volatile unsigned int AHB1LPENR;    // 0x50     
    volatile unsigned int AHB2LPENR;    // 0x54
    volatile unsigned int AHB3LPENR;    // 0x58
    volatile unsigned int RESERVED4;    // 0x5C
    volatile unsigned int APB1LPENR;    // 0x60
    volatile unsigned int APB2LPENR;    // 0x64
    volatile unsigned int RESERVED5[2]; // 0x68, 0x6C
    volatile unsigned int BDCR;         // 0x70
    volatile unsigned int CSR;          // 0x74
    volatile unsigned int RESERVED6[2]; // 0x78, 0x7C
    volatile unsigned int SSCGR;        // 0x80
    volatile unsigned int PLLI2SCFGR;   // 0x84
    volatile unsigned int PLLSAICFGR;   // 0x88
    volatile unsigned int DCKCFGR;      // 0x8C
    volatile unsigned int CKGATENR;     // 0x90
    volatile unsigned int DCKCFGR2;     // 0x94
} Rcc_t;

#define Rcc ((Rcc_t *) RCC_BASE)

// API
/**
 * @brief Aktiviert den AHB1-Takt für einen GPIO-Port anhand seiner Basisadresse.
 *
 * Diese Funktion erkennt automatisch, welcher GPIO-Port (A–H) gemeint ist,
 * und setzt das zugehörige GPIOxEN-Bit im Register RCC->AHB1ENR.
 *
 * Sie ist für alle Ports GPIOA bis GPIOH gültig.
 *
 * @param[in] portBase Die Basisadresse des gewünschten GPIO-Ports
 *                     (z.B. 0x40020000 für GPIOA oder (uint32_t)GpioA).
 *
 * @retval 0  Erfolg: Takt wurde aktiviert.
 * @retval -1 Fehler: Unbekannte oder ungültige Portadresse.
 *
 * @note Diese Funktion muss vor der Konfiguration eines GPIO-Ports aufgerufen werden,
 *       sofern nicht eine andere Funktion dies automatisch übernimmt (z.B. bmlGpioInitSimple()).
 *
 * @code
 * // Beispiel: Takt für GPIOA aktivieren
 * if (bmlRccEnableGpioClock((uint32_t)GpioA) != 0) {
 *     // Fehlerbehandlung
 * }
 * @endcode
 */
int bmlRccEnableGpioClock(unsigned int portBase);

/**
 * @brief Aktiviert den APB1-Takt für die UART2-Peripherie.
 *
 * Diese Funktion setzt das USART2EN-Bit im Register RCC->APB1ENR,
 * um den Takt für UART2 zu aktivieren.
 *
 * Sie wird typischerweise vor der Initialisierung von UART2 aufgerufen
 * oder automatisch durch bmlUart2Init().
 *
 * @retval 0 Erfolg: Takt wurde aktiviert.
 * @retval -1 Fehler: ungültige Systemkonfiguration (nicht vorgesehen für STM32F446RE)
 *
 * @note Muss vor Zugriff auf UART2-Register ausgeführt werden, falls nicht automatisch aktiviert.
 *
 * @code
 * // Beispiel: UART2-Takt explizit freigeben
 * if (bmlRccEnableUart2Clock() != 0) {
 *     // Fehlerbehandlung
 * }
 * @endcode
 */
int bmlRccEnableUart2Clock(void);

int bmlRccEnableTim3Clock(void);

#endif // BML_RCC_H

/** @} */
