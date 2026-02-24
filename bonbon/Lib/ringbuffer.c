#include "ringbuffer.h"

void RingBuffer_Init(RingBuffer_t *rb) {
    rb->writePointer = 0;
    rb->readPointer = 0;
    rb->overflow = 0;
    rb->telegramCnt = 0;
}

int RingBuffer_IsEmpty(RingBuffer_t *rb) {
    return rb->writePointer == rb->readPointer;
}

int RingBuffer_IsFull(RingBuffer_t *rb) {
    return ((rb->writePointer + 1) % RINGBUF_SIZE) == rb->readPointer;
}

unsigned int RingBuffer_Count(RingBuffer_t *rb) {
    if (rb->writePointer >= rb->readPointer)
        return rb->writePointer - rb->readPointer;
    return RINGBUF_SIZE - rb->readPointer + rb->writePointer;
}

void RingBuffer_Put(RingBuffer_t *rb, char ch) {
    if (RingBuffer_IsFull(rb)) {
        rb->overflow++;
        return;
    }
    rb->buffer[rb->writePointer] = ch;
    rb->writePointer = (rb->writePointer + 1) % RINGBUF_SIZE;
}

char RingBuffer_Get(RingBuffer_t *rb) {
    if (RingBuffer_IsEmpty(rb)) return 0;
    char ch = rb->buffer[rb->readPointer];
    rb->readPointer = (rb->readPointer + 1) % RINGBUF_SIZE;
    return ch;
}