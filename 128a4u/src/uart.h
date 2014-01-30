/*
 * uart.h
 *
 * Created: 1/23/2014 9:39:53 PM
 *  Author: rayme_001
 */ 


#ifndef UART_H_
#define UART_H_

#define USART_BAUDRATE 9600 //Baudrate van usart

#ifdef F_CPU
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1) //Macro om de baud te prescalen met de clock (F_CPU) rate (?)
#endif

#define RX_BUFFER_SIZE 128				//		uart

struct ring_buffer {					//		uart
	char buffer[RX_BUFFER_SIZE];
	int head;
	int tail;
};

typedef struct ring_buffer ring_buffer; // uart

void store_char(char c, ring_buffer* rx_buffer);

#endif /* UART_H_ */