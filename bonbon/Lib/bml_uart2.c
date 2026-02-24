#include "bml_uart2.h"
#include "bml_rcc.h"
#include "bml_gpio.h"
#include "bml_nvic.h"

#define F_CPU 16000000UL  // Standard-HSI-Takt

RingBuffer_t uart2RxBuffer;



UartStatus_t bmlUart2Init(uint32_t baudrate) {
    if (baudrate == 0) return UART_ERROR_BAUDRATE;
    RingBuffer_Init(&uart2RxBuffer);

    bmlRccEnableUart2Clock();
    

    bmlGpioInitSimple(PA2, GPIO_MODE_ALTFN);
    bmlGpioSetAltFn(PA2, GPIO_AF_USART2);
    bmlGpioInitSimple(PA3, GPIO_MODE_ALTFN);
    bmlGpioSetAltFn(PA3, GPIO_AF_USART2);

    
    Uart2->BRR.all = (F_CPU + (baudrate / 2)) / baudrate;
    Uart2->CR1.bits.M =  UART_8N1;
    Uart2->CR1.bits.PCE = UART_DISABLE;           // No Parity
    Uart2->CR1.bits.OVER8 = UART_OVERSAMPLING_16; // Oversampling x16
    Uart2->CR1.bits.TE = UART_ENABLE;             // Enable Transmitter
    Uart2->CR1.bits.RE = UART_ENABLE;             // Enable Receiver
    Uart2->CR1.bits.UE = UART_ENABLE;             // Enable Uart
    Uart2->CR2.bits.STOP = UART_STOPBITS_1;       // 1 Stopbit
    Uart2->CR3.bits.CTSE = UART_DISABLE;          // No Hardwarecontrol
    Uart2->CR3.bits.RTSE = UART_DISABLE;          // No Hardwarecontrol

    Uart2->CR1.bits.RXNEIE = UART_ENABLE;         // Enable RX Interrupt
    bmlNvicEnableIrq(USART2_IRQn);                // Enable UART in NVIC
    return UART_OK;
}

// TODO: Senden auch über Interrupt
void bmlUart2WriteChar(char ch) {
    while (!Uart2->SR.bits.TXE);
    Uart2->DR.all = (uint32_t)ch;
}

void bmlUart2WriteString(const char *str) {
    while (*str) {
        bmlUart2WriteChar(*str++);
    }
}

__attribute__((weak)) void bmlUart2OnRxCallback(char ch) {
    RingBuffer_Put(&uart2RxBuffer,ch);
    if(ch=='\r'){
      uart2RxBuffer.telegramCnt++;
    }
}

void USART2_IRQHandler(void) {
    if (Uart2->SR.all & (1 << 5)) {
        char ch = (char)(Uart2->DR.all & 0xFF);
        bmlUart2OnRxCallback(ch);
        bmlUart2WriteChar(ch);//ECHO
        if(ch=='\r') bmlUart2WriteChar('\n');
    }
}







