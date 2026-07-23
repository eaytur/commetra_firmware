/**
 * @brief Single Producer / Single Consumer (SPSC) ring buffer.
 *
 * One slot is intentionally left unused to distinguish
 * between full and empty states without requiring an
 * additional counter or full flag.
 *
 * Empty: head == tail
 * Full : (head + 1) % capacity == tail
 *
 * This design is suitable for ISR (producer) and Task
 * (consumer) communication without locks.
 */

#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    RING_BUFFER_OK = 0,
    RING_BUFFER_NULL_PTR,
    RING_BUFFER_INVALID_CAPACITY,
    RING_BUFFER_FULL,
    RING_BUFFER_EMPTY
} RingBufferStatus;

typedef struct
{
    uint8_t *storage;
    size_t capacity;
    volatile size_t head;
    volatile size_t tail;
} RingBuffer;

RingBufferStatus RingBuffer_Init(RingBuffer *ringBuffer, uint8_t *storage, size_t capacity);
RingBufferStatus RingBuffer_Push(RingBuffer *ringBuffer, uint8_t data);
RingBufferStatus RingBuffer_Pop(RingBuffer *ringBuffer, uint8_t *data);
bool RingBuffer_IsEmpty(const RingBuffer *ringBuffer);
bool RingBuffer_IsFull(const RingBuffer *ringBuffer);

#endif /* RING_BUFFER_H */