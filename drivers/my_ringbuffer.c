/*
 * my_ringbuffer.c
 *
 *  Created on: Dec 23, 2024
 *      Author: nvd
 */


#include "my_ringbuffer.h"

// Initialize the Ring Buffer
// This function sets the head and tail pointers to 0, preparing the buffer for use.
void RingBuffer_Init(RingBuffer *rb) {
    rb->head = 0;
    rb->tail = 0;
}

// Check if the Ring Buffer is empty
// Returns true if the buffer is empty, false otherwise.
bool RingBuffer_IsEmpty(RingBuffer *rb) {
    return rb->head == rb->tail;
}

// Check if the Ring Buffer is full
// Returns true if the buffer is full, false otherwise.
bool RingBuffer_IsFull(RingBuffer *rb) {
    return (rb->head + 1) % BUFFER_SIZE == rb->tail;
}

// Add data to the Ring Buffer
// If the buffer is full, new data is not added (overflow).
// The head pointer is updated after adding the data.
void RingBuffer_Add(RingBuffer *rb, uint8_t data) {
    // Check if the buffer is full, if full, data is not added
    if (!RingBuffer_IsFull(rb)) {
        rb->buffer[rb->head] = data;
        rb->head = (rb->head + 1) % BUFFER_SIZE;  // Circular increment
    }
}

// Get data from the Ring Buffer
// If the buffer is empty, returns 0 (or any other error value).
// The tail pointer is updated after retrieving the data.
uint8_t RingBuffer_Get(RingBuffer *rb) {
    uint8_t data = 0;

    // If the buffer is not empty, get the data and update the tail pointer
    if (!RingBuffer_IsEmpty(rb)) {
        data = rb->buffer[rb->tail];
        rb->tail = (rb->tail + 1) % BUFFER_SIZE;  // Circular increment
    }

    return data;
}
