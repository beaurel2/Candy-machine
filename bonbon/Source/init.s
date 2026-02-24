// start.s
// Minimal Startup Init  


// ************************************************

        .syntax unified


// ************************************************
// Macros

.macro ISR_HANDLER Name=
        // Insert vector in vector table
        .section .vectors, "ax"
        .word \Name
        // Insert dummy handler in init section
        .section .init.\Name, "ax"
        .thumb_func
        .weak \Name
        .balign 2
\Name:
        1: b 1b   // Endless loop

.endm


.macro ISR_RESERVED
        .section .vectors, "ax"
        .word 0
.endm

.macro MARK_FUNC Name
        .global \Name
        .thumb_func
        .code 16
\Name:
.endm

#undef L
#define L(label) .L_start_##label
// ************************************************
// extern
 
        .extern __stack_end__     // kommt von Linkersript und  Project -> Options -> Runtime Memory Area


// ************************************************
// Reset Handler 
        .global reset_handler
        .global Reset_Handler
        .equ reset_handler, Reset_Handler
        .section .init.Reset_Handler, "ax"
        .balign 2
        .thumb_func
//Reset:
Reset_Handler:
_start:                           // Label für Debugger
        ldr sp, =__initial_sp     // Setze den Stackpointer auf den Anfang des Stacks // Toolchain wird übergangen
// Init Segger spezifisch 
        ldr     R4, =__SEGGER_init_table__      // Set table pointer to start of initialization table
L(RunInit): 
        ldr     R0, [R4]                        // Get next initialization function from table
        adds    R4, R4, #4                      // Increment table pointer to point to function arguments
        blx     R0                              // Call initialization function
        b       L(RunInit)
        //
MARK_FUNC __SEGGER_init_done
MARK_FUNC __startup_complete
// End Init Segger spezifisch
        mov r0, #0
        mov r1, #0
        mov r2, #0
        mov r3, #0
        mov r4, #0
        mov r5, #0
        mov r6, #0
        mov r7, #0
        mov r8, #0
        mov r9, #0
        mov r10, #0
        mov r11, #0
        mov r12, #0
        ldr SP, =__stack_end__




        bl      main
        b       .

// ************************************************
  // Stack
  .global __initial_sp
  // Stack Allocation: 1 KB nach benutzten Daten
  .section  .stack               // Bereich für uninitialisierte Daten
            .align 2            // 32-Bit-Ausrichtung (4 Byte)
  Stack:    .space 0x4000       // Reserviert 16 KB (16*0x400 Bytes) für den Stack

  // Initialisiere den Stack Pointer in einer initialisierten Sektion
  .section .data            
  __initial_sp:
           .word   Stack + 0x4000  // Stack Pointer zeigt auf das Ende des Stackbereichs


// ************************************************
// Vector Table
        .section .vectors, "ax"
        .code 16
        .balign 512
        .global _vectors
_vectors:
        .word __stack_end__             // kommt von Linkersript und  Project -> Options -> Runtime Memory Area 
                                        // wird manuell überschrieben (Reset Handler)
        .word Reset_Handler
        .word NMI_Handler
        .word HardFault_Handler
        .word   0                        // 7 unused System Interrupts
        .word   0
        .word   0
        .word   0
        .word   0
        .word   0
        .word   0
        .word   0                        // ** Supervisor Call **
        .word   0                        // 3 unused System Interrupts
        .word   0
        .word   0
        ISR_HANDLER SysTick_Handler          // ** System Tick Timer **
        ISR_HANDLER WWDG_IRQHandler
        ISR_HANDLER PVD_IRQHandler
        ISR_HANDLER TAMP_STAMP_IRQHandler
        ISR_HANDLER RTC_WKUP_IRQHandler
        ISR_HANDLER FLASH_IRQHandler
        ISR_HANDLER RCC_IRQHandler
        ISR_HANDLER EXTI0_IRQHandler
        ISR_HANDLER EXTI1_IRQHandler
        ISR_HANDLER EXTI2_IRQHandler
        ISR_HANDLER EXTI3_IRQHandler
        ISR_HANDLER EXTI4_IRQHandler
        ISR_HANDLER DMA1_Stream0_IRQHandler
        ISR_HANDLER DMA1_Stream1_IRQHandler
        ISR_HANDLER DMA1_Stream2_IRQHandler
        ISR_HANDLER DMA1_Stream3_IRQHandler
        ISR_HANDLER DMA1_Stream4_IRQHandler
        ISR_HANDLER DMA1_Stream5_IRQHandler
        ISR_HANDLER DMA1_Stream6_IRQHandler
        ISR_HANDLER ADC_IRQHandler
        ISR_HANDLER CAN1_TX_IRQHandler
        ISR_HANDLER CAN1_RX0_IRQHandler
        ISR_HANDLER CAN1_RX1_IRQHandler
        ISR_HANDLER CAN1_SCE_IRQHandler
        ISR_HANDLER EXTI9_5_IRQHandler
        ISR_HANDLER TIM1_BRK_TIM9_IRQHandler
        ISR_HANDLER TIM1_UP_TIM10_IRQHandler
        ISR_HANDLER TIM1_TRG_COM_TIM11_IRQHandler
        ISR_HANDLER TIM1_CC_IRQHandler
        ISR_HANDLER TIM2_IRQHandler
        ISR_HANDLER TIM3_IRQHandler
        ISR_HANDLER TIM4_IRQHandler
        ISR_HANDLER I2C1_EV_IRQHandler
        ISR_HANDLER I2C1_ER_IRQHandler
        ISR_HANDLER I2C2_EV_IRQHandler
        ISR_HANDLER I2C2_ER_IRQHandler
        ISR_HANDLER SPI1_IRQHandler
        ISR_HANDLER SPI2_IRQHandler
        ISR_HANDLER USART1_IRQHandler
        ISR_HANDLER USART2_IRQHandler
        ISR_HANDLER USART3_IRQHandler
        ISR_HANDLER EXTI15_10_IRQHandler
        ISR_HANDLER RTC_Alarm_IRQHandler
        ISR_HANDLER OTG_FS_WKUP_IRQHandler
        ISR_HANDLER TIM8_BRK_TIM12_IRQHandler
        ISR_HANDLER TIM8_UP_TIM13_IRQHandler
        ISR_HANDLER TIM8_TRG_COM_TIM14_IRQHandler
        ISR_HANDLER TIM8_CC_IRQHandler
        ISR_HANDLER DMA1_Stream7_IRQHandler
        ISR_HANDLER FMC_IRQHandler
        ISR_HANDLER SDIO_IRQHandler
        ISR_HANDLER TIM5_IRQHandler
        ISR_HANDLER SPI3_IRQHandler
        ISR_HANDLER UART4_IRQHandler
        ISR_HANDLER UART5_IRQHandler
        ISR_HANDLER TIM6_DAC_IRQHandler
        ISR_HANDLER TIM7_IRQHandler
        ISR_HANDLER DMA2_Stream0_IRQHandler
        ISR_HANDLER DMA2_Stream1_IRQHandler
        ISR_HANDLER DMA2_Stream2_IRQHandler
        ISR_HANDLER DMA2_Stream3_IRQHandler
        ISR_HANDLER DMA2_Stream4_IRQHandler
        ISR_RESERVED
        ISR_RESERVED
        ISR_HANDLER CAN2_TX_IRQHandler
        ISR_HANDLER CAN2_RX0_IRQHandler
        ISR_HANDLER CAN2_RX1_IRQHandler
        ISR_HANDLER CAN2_SCE_IRQHandler
        ISR_HANDLER OTG_FS_IRQHandler
        ISR_HANDLER DMA2_Stream5_IRQHandler
        ISR_HANDLER DMA2_Stream6_IRQHandler
        ISR_HANDLER DMA2_Stream7_IRQHandler
        ISR_HANDLER USART6_IRQHandler
        ISR_HANDLER I2C3_EV_IRQHandler
        ISR_HANDLER I2C3_ER_IRQHandler
        ISR_HANDLER OTG_HS_EP1_OUT_IRQHandler
        ISR_HANDLER OTG_HS_EP1_IN_IRQHandler
        ISR_HANDLER OTG_HS_WKUP_IRQHandler
        ISR_HANDLER OTG_HS_IRQHandler
        ISR_HANDLER DCMI_IRQHandler
        ISR_RESERVED
        ISR_RESERVED
        ISR_HANDLER FPU_IRQHandler
        ISR_RESERVED
        ISR_RESERVED
        ISR_HANDLER SPI4_IRQHandler
        ISR_RESERVED
        ISR_RESERVED
        ISR_HANDLER SAI1_IRQHandler
        ISR_RESERVED
        ISR_RESERVED
        ISR_RESERVED
        ISR_HANDLER SAI2_IRQHandler
        ISR_HANDLER QUADSPI_IRQHandler
        ISR_HANDLER CEC_IRQHandler
        ISR_HANDLER SPDIF_RX_IRQHandler
        ISR_HANDLER FMPI2C1_EV_IRQHandler
        ISR_HANDLER FMPI2C1_ER_IRQHandler

// ************************************************
// System Interrupts
NMI_Handler:
    b   .   // Unendliche Schleife bei NMI-Fehler
HardFault_Handler:
    b   .   // Unendliche Schleife bei HardFault

.end