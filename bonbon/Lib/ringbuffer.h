/**
 * @file bml_ringbuffer.h
 * @brief Einfacher Ringpuffer für UART-Empfang im BareMetal STM32F446RE-System
 *
 * @defgroup BML_RINGBUFFER Ringpuffer
 * @brief Funktionen zur Initialisierung und Nutzung eines UART-Ringspeichers
 * @{
 */

#ifndef BML_RINGBUFFER_H
#define BML_RINGBUFFER_H

#define RINGBUF_SIZE 128

/**
 * @brief Struktur eines einfachen Ringpuffers.
 */
typedef struct {
    char buffer[RINGBUF_SIZE];          ///< Datenspeicher
    volatile unsigned int writePointer; ///< Schreibzeiger
    volatile unsigned int readPointer;  ///< Lesezeiger
    volatile unsigned int overflow;     ///< Zähler für Überläufe
    volatile unsigned int telegramCnt;  ///< Zähler für abgeschlossene Telegramme (optional)
} RingBuffer_t;

/**
 * @brief Initialisiert einen Ringpuffer.
 *
 * @param rb Zeiger auf die RingBuffer-Struktur.
 *
 * @code
 * RingBuffer_Init(&uart2RxBuffer);
 * @endcode
 */
void RingBuffer_Init(RingBuffer_t *rb);

/**
 * @brief Prüft, ob der Ringpuffer leer ist.
 *
 * @param rb Zeiger auf RingBuffer.
 * @retval 1 Wenn leer.
 * @retval 0 Wenn mindestens ein Zeichen vorhanden ist.
 *
 * @code
 * if (RingBuffer_IsEmpty(&uart2RxBuffer)) {
 *     // Warte auf neue Daten
 * }
 * @endcode
 */
int RingBuffer_IsEmpty(RingBuffer_t *rb);

/**
 * @brief Prüft, ob der Ringpuffer voll ist.
 *
 * @param rb Zeiger auf RingBuffer.
 * @retval 1 Wenn voll.
 * @retval 0 Wenn noch Platz vorhanden ist.
 *
 * @code
 * if (RingBuffer_IsFull(&uart2RxBuffer)) {
 *     // Pufferüberlauf vermeiden
 * }
 * @endcode
 */
int RingBuffer_IsFull(RingBuffer_t *rb);

/**
 * @brief Gibt die Anzahl der gespeicherten Zeichen im Puffer zurück.
 *
 * @param rb Zeiger auf RingBuffer.
 * @return Anzahl der belegten Bytes im Ringpuffer.
 *
 * @code
 * unsigned int n = RingBuffer_Count(&uart2RxBuffer);
 * @endcode
 */
unsigned int RingBuffer_Count(RingBuffer_t *rb);

/**
 * @brief Fügt ein Zeichen in den Ringpuffer ein.
 *
 * Falls der Puffer voll ist, wird das Zeichen verworfen und der Overflow-Zähler erhöht.
 *
 * @param rb Zeiger auf RingBuffer.
 * @param ch Zeichen, das gespeichert werden soll.
 *
 * @code
 * RingBuffer_Put(&uart2RxBuffer, 'x');
 * @endcode
 */
void RingBuffer_Put(RingBuffer_t *rb, char ch);

/**
 * @brief Liest ein Zeichen aus dem Ringpuffer.
 *
 * @param rb Zeiger auf RingBuffer.
 * @return Erstes gespeichertes Zeichen, oder 0 wenn der Puffer leer ist.
 *
 * @code
 * char c = RingBuffer_Get(&uart2RxBuffer);
 * @endcode
 */
char RingBuffer_Get(RingBuffer_t *rb);

#endif // BML_RINGBUFFER_H

/** @} */
