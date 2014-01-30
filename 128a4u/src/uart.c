/*
 * uart.c
 *
 * Created: 1/24/2014 8:50:23 AM
 *  Author: rayme_001
 */ 

#include "uart.h"

/* Character in een ring buffer struct douwen */
void store_char(char c, ring_buffer* rx_buffer)
{
	int i = (rx_buffer->head + 1) % RX_BUFFER_SIZE;

	// if we should be storing the received character into the location
	// just before the tail (meaning that the head would advance to the
	// current location of the tail), we're about to overflow the buffer
	// and so we don't write the character or advance the head.
	if (i != rx_buffer->tail) {
		rx_buffer->buffer[rx_buffer->head] = c;
		rx_buffer->head = i;
	}
}