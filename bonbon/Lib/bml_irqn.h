/**
 * @file bml_irqn.h
 * @brief Definition aller NVIC-IRQ-Nummern für den STM32F446RE
 *
 * @defgroup BML_IRQN NVIC Interruptnummern
 * @brief Enum für die Verwendung in NVIC-Konfigurationen
 * @{
 */

#ifndef BML_IRQN_H
#define BML_IRQN_H

/**
 * @brief IRQ-Nummern für alle NVIC-fähigen Peripheriekomponenten.
 *
 * Dieses Enum wird verwendet, um Interruptnummern systematisch und lesbar
 * z.B. in Kombination mit `bmlNvicEnableIrq()` oder `bmlNvicSetPriority()` zu verwenden.
 *
 * @code
 * bmlNvicEnableIrq(USART2_IRQn);
 * bmlNvicSetPriority(EXTI0_IRQn, 3);
 * @endcode
 */
typedef enum {
    WWDG_IRQn           = 0,   /**< Window Watchdog interrupt */
    PVD_IRQn            = 1,   /**< PVD through EXTI line detection */
    TAMP_STAMP_IRQn     = 2,   /**< Tamper and TimeStamp interrupts */
    RTC_WKUP_IRQn       = 3,   /**< RTC Wakeup interrupt */
    FLASH_IRQn          = 4,   /**< Flash global interrupt */
    RCC_IRQn            = 5,   /**< RCC global interrupt */
    EXTI0_IRQn          = 6,   /**< EXTI Line0 interrupt */
    EXTI1_IRQn          = 7,
    EXTI2_IRQn          = 8,
    EXTI3_IRQn          = 9,
    EXTI4_IRQn          = 10,
    DMA1_Stream0_IRQn   = 11,
    DMA1_Stream1_IRQn   = 12,
    DMA1_Stream2_IRQn   = 13,
    DMA1_Stream3_IRQn   = 14,
    DMA1_Stream4_IRQn   = 15,
    DMA1_Stream5_IRQn   = 16,
    DMA1_Stream6_IRQn   = 17,
    ADC_IRQn            = 18,
    CAN1_TX_IRQn        = 19,
    CAN1_RX0_IRQn       = 20,
    CAN1_RX1_IRQn       = 21,
    CAN1_SCE_IRQn       = 22,
    EXTI9_5_IRQn        = 23,
    TIM1_BRK_TIM9_IRQn  = 24,
    TIM1_UP_TIM10_IRQn  = 25,
    TIM1_TRG_COM_TIM11_IRQn = 26,
    TIM1_CC_IRQn        = 27,
    TIM2_IRQn           = 28,
    TIM3_IRQn           = 29,
    TIM4_IRQn           = 30,
    I2C1_EV_IRQn        = 31,
    I2C1_ER_IRQn        = 32,
    I2C2_EV_IRQn        = 33,
    I2C2_ER_IRQn        = 34,
    SPI1_IRQn           = 35,
    SPI2_IRQn           = 36,
    USART1_IRQn         = 37,
    USART2_IRQn         = 38,
    USART3_IRQn         = 39,
    EXTI15_10_IRQn      = 40,
    RTC_Alarm_IRQn      = 41,
    OTG_FS_WKUP_IRQn    = 42,
    TIM8_BRK_TIM12_IRQn = 43,
    TIM8_UP_TIM13_IRQn  = 44,
    TIM8_TRG_COM_TIM14_IRQn = 45,
    TIM8_CC_IRQn        = 46,
    DMA1_Stream7_IRQn   = 47,
    FSMC_IRQn           = 48,
    SDIO_IRQn           = 49,
    TIM5_IRQn           = 50,
    SPI3_IRQn           = 51,
    UART4_IRQn          = 52,
    UART5_IRQn          = 53,
    TIM6_DAC_IRQn       = 54,
    TIM7_IRQn           = 55,
    DMA2_Stream0_IRQn   = 56,
    DMA2_Stream1_IRQn   = 57,
    DMA2_Stream2_IRQn   = 58,
    DMA2_Stream3_IRQn   = 59,
    DMA2_Stream4_IRQn   = 60,
    ETH_IRQn            = 61,
    ETH_WKUP_IRQn       = 62,
    CAN2_TX_IRQn        = 63,
    CAN2_RX0_IRQn       = 64,
    CAN2_RX1_IRQn       = 65,
    CAN2_SCE_IRQn       = 66,
    OTG_FS_IRQn         = 67,
    DMA2_Stream5_IRQn   = 68,
    DMA2_Stream6_IRQn   = 69,
    DMA2_Stream7_IRQn   = 70,
    USART6_IRQn         = 71,
    I2C3_EV_IRQn        = 72,
    I2C3_ER_IRQn        = 73,
    FPU_IRQn            = 81
} IrqNumber_t;

#endif // BML_IRQN_H

/** @} */
