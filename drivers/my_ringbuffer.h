/*
 * my_ringbuffer.h
 *
 *  Created on: Dec 23, 2024
 *      Author: nvd
 */

#ifndef MY_RINGBUFFER_H_
#define MY_RINGBUFFER_H_

#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 128  // Define the buffer size

// Ring Buffer structure definition
typedef struct {
    uint8_t buffer[BUFFER_SIZE];  // Buffer to store data
    volatile uint8_t head;        // Index to add new data (write)
    volatile uint8_t tail;        // Index to read data
} RingBuffer;

// Function prototypes
void RingBuffer_Init(RingBuffer *rb);               // Initialize the buffer
bool RingBuffer_IsEmpty(RingBuffer *rb);            // Check if the buffer is empty
bool RingBuffer_IsFull(RingBuffer *rb);             // Check if the buffer is full
void RingBuffer_Add(RingBuffer *rb, uint8_t data);  // Add data to the buffer
uint8_t RingBuffer_Get(RingBuffer *rb);             // Get data from the buffer


#endif /* MY_RINGBUFFER_H_ */
