/**
 * @file bml_uart2.h
 * @brief BareMetal UART2-Modul für den STM32F446RE
 *
 * @defgroup BML_UART2 UART2-Treiber
 * @brief Funktionen zur Initialisierung und Kommunikation über UART2
 * @{
 */

#ifndef BML_UART2_H
#define BML_UART2_H

#include "ringbuffer.h"

// ---------- Bitfelder ----------

// USART_SR
typedef union {
    struct {
        unsigned int PE     : 1;
        unsigned int FE     : 1;
        unsigned int NF     : 1;
        unsigned int ORE    : 1;
        unsigned int IDLE   : 1;
        unsigned int RXNE   : 1;
        unsigned int TC     : 1;
        unsigned int TXE    : 1;
        unsigned int LBD    : 1;
        unsigned int CTS    : 1;
        unsigned int        : 22;
    } bits;
    unsigned int all;
} UartSR_t;

// USART_DR
typedef union {
    struct {
        unsigned int DR     : 9;
        unsigned int        : 23;
    } bits;
    unsigned int all;
} UartDR_t;

// USART_BRR
typedef union {
    struct {
        unsigned int DIV_Fraction : 4;
        unsigned int DIV_Mantissa : 12;
        unsigned int              : 16;
    } bits;
    unsigned int all;
} UartBRR_t;

// USART_CR1
typedef union {
    struct {
        unsigned int SBK     : 1;
        unsigned int RWU     : 1;
        unsigned int RE      : 1;
        unsigned int TE      : 1;
        unsigned int IDLEIE  : 1;
        unsigned int RXNEIE  : 1;
        unsigned int TCIE    : 1;
        unsigned int TXEIE   : 1;
        unsigned int PEIE    : 1;
        unsigned int PS      : 1;
        unsigned int PCE     : 1;
        unsigned int WAKE    : 1;
        unsigned int M       : 1;
        unsigned int UE      : 1;
        unsigned int         : 1;
        unsigned int OVER8   : 1;
        unsigned int         : 16;
    } bits;
    unsigned int all;
} UartCR1_t;

// USART_CR2
typedef union {
    struct {
        unsigned int ADD     : 4;
        unsigned int         : 1;
        unsigned int LBDL    : 1;
        unsigned int LBDIE   : 1;
        unsigned int         : 1;
        unsigned int LBCL    : 1;
        unsigned int CPHA    : 1;
        unsigned int CPOL    : 1;
        unsigned int CLKEN   : 1;
        unsigned int STOP    : 2;
        unsigned int LINEN   : 1;
        unsigned int         : 17;
    } bits;
    unsigned int all;
} UartCR2_t;

// USART_CR3
typedef union {
    struct {
        unsigned int EIE     : 1;
        unsigned int IREN    : 1;
        unsigned int IRLP    : 1;
        unsigned int HDSEL   : 1;
        unsigned int NACK    : 1;
        unsigned int SCEN    : 1;
        unsigned int DMAR    : 1;
        unsigned int DMAT    : 1;
        unsigned int RTSE    : 1;
        unsigned int CTSE    : 1;
        unsigned int CTSIE   : 1;
        unsigned int ONEBIT  : 1;
        unsigned int         : 20;
    } bits;
    unsigned int all;
} UartCR3_t;

// USART_GTPR
typedef union {
    struct {
        unsigned int PSC     : 8;
        unsigned int GT      : 8;
        unsigned int         : 16;
    } bits;
    unsigned int all;
} UartGTPR_t;

// ---------- USART Basisstruktur ----------
typedef struct {
    volatile UartSR_t  SR;
    volatile UartDR_t  DR;
    volatile UartBRR_t BRR;
    volatile UartCR1_t CR1;
    volatile UartCR2_t CR2;
    volatile UartCR3_t CR3;
    volatile UartCR1_t GTPR;
} Uart_t;

#define USART2_BASE (0x40004400UL)
#define Uart2 ((Uart_t *) USART2_BASE)

typedef enum {
    UART_8N1 = 0x0,
    UART_9N1 = 0x1
} UartWordLength_t;

typedef enum {
    UART_DISABLE = 0,
    UART_ENABLE  = 1
}UartEnable_t;

typedef enum {
    UART_OVERSAMPLING_16 = 0,
    UART_OVERSAMPLING_8  = 1
}UartOver_t;

typedef enum {
    UART_PARITY_EVEN = 0,
    UART_PARITY_ODD  = 1
}UartParity_t;

typedef enum {
    UART_STOPBITS_1   = 0x0,
    UART_STOPBITS_0_5 = 0x1,
    UART_STOPBITS_2   = 0x2,
    UART_STOPBITS_1_5 = 0x3
}UartStopBits_t;


// ---------- Statuswerte ----------
typedef enum {
    UART_OK = 0,
    UART_ERROR_BAUDRATE = -1
} UartStatus_t;





extern RingBuffer_t uart2RxBuffer;
// ---------- API ----------

/**
 * @brief Initialisiert UART2 mit gewünschter Baudrate.
 *
 * Diese Funktion konfiguriert UART2 für 8N1, aktiviert den Takt und initialisiert die Hardware.
 *
 * @param baudrate Gewünschte Baudrate (z.B. 9600, 115200)
 * @retval UART_OK bei Erfolg
 * @retval UART_ERROR_BAUDRATE bei ungültiger Baudrate
 *
 * @code
 * bmlUart2Init(115200);
 * @endcode
 */
UartStatus_t bmlUart2Init(unsigned int baudrate);

/**
 * @brief Sendet ein einzelnes Zeichen über UART2.
 *
 * Wartet blockierend, bis das Datenregister leer ist.
 *
 * @param ch Zu sendendes Zeichen
 *
 * @code
 * bmlUart2WriteChar('A');
 * @endcode
 */
void bmlUart2WriteChar(char ch);

/**
 * @brief Sendet eine nullterminierte Zeichenkette über UART2.
 *
 * @param str Zeiger auf String
 *
 * @code
 * bmlUart2WriteString("Hello UART\\n");
 * @endcode
 */
void bmlUart2WriteString(const char *str);

/**
 * @brief Liest ein einzelnes Zeichen von UART2 (blockierend).
 *
 * @return Empfangenes Zeichen
 *
 * @code
 * char c = bmlUart2ReadChar();
 * @endcode
 */
char bmlUart2ReadChar(void);

/**
 * @brief Aktiviert den RX-Interrupt für UART2.
 *
 * Die Empfangs-ISR ruft bmlUart2OnRxCallback auf.
 *
 * @code
 * bmlUart2EnableRxInterrupt();
 * @endcode
 */
void bmlUart2EnableRxInterrupt(void);

/**
 * @brief Callback-Funktion bei UART2 RX-Interrupt.
 *
 * Wird von der ISR aufgerufen, wenn ein Zeichen empfangen wurde.
 * Diese Funktion sollte vom Benutzer implementiert werden.
 *
 * @param ch Empfangenes Zeichen
 *
 * @code
 * void bmlUart2OnRxCallback(char ch) {
 *     RingBuffer_Put(&uart2RxBuffer, ch);
 * }
 * @endcode
 */
void bmlUart2OnRxCallback(char ch);



#endif // BML_UART2_H

/** @} */
