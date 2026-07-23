#include "ring_buffer.h"

#include <assert.h>

RingBufferStatus RingBuffer_Init(RingBuffer *ringBuffer,
                                 uint8_t *storage,
                                 size_t capacity)
{
    if ((ringBuffer == NULL) || (storage == NULL))
    {
        return RING_BUFFER_NULL_PTR;
    }

    if (capacity < 2U)
    {
        return RING_BUFFER_INVALID_CAPACITY;
    }

    ringBuffer->storage = storage;
    ringBuffer->capacity = capacity;
    ringBuffer->head = 0U;
    ringBuffer->tail = 0U;

    return RING_BUFFER_OK;
}

bool RingBuffer_IsEmpty(const RingBuffer *ringBuffer)
{
    assert(ringBuffer != NULL);

    return (ringBuffer->head == ringBuffer->tail);
}

bool RingBuffer_IsFull(const RingBuffer *ringBuffer)
{
    assert(ringBuffer != NULL);

    size_t nextHead =
        (ringBuffer->head + 1U) % ringBuffer->capacity;

    return (nextHead == ringBuffer->tail);
}

RingBufferStatus RingBuffer_Push(RingBuffer *ringBuffer,
                                 uint8_t data)
{
    size_t nextHead = (ringBuffer->head + 1U) % ringBuffer->capacity;

    if (ringBuffer == NULL)
    {
        return RING_BUFFER_NULL_PTR;
    }

    if (RingBuffer_IsFull(ringBuffer))
    {
        return RING_BUFFER_FULL;
    }

    ringBuffer->storage[ringBuffer->head] = data;

    ringBuffer->head = nextHead;

    return RING_BUFFER_OK;
}

RingBufferStatus RingBuffer_Pop(RingBuffer *ringBuffer,
                                uint8_t *data)
{
    if ((ringBuffer == NULL) || (data == NULL))
    {
        return RING_BUFFER_NULL_PTR;
    }

    if (RingBuffer_IsEmpty(ringBuffer))
    {
        return RING_BUFFER_EMPTY;
    }

    *data = ringBuffer->storage[ringBuffer->tail];

    ringBuffer->tail =
        (ringBuffer->tail + 1U) % ringBuffer->capacity;

    return RING_BUFFER_OK;
}