/*
* bluetooth.c
*
* Created: 1/23/2014 9:31:40 PM
*  Author: rayme_001
*/

#include "debug.h"

ring_buffer rx_buffer_c1 = { { 0 }, 0, 0 };

void InitializeDebug(void) {
	//powerOnBT();
	
	// Set Tx pin to an output
	PORTC.DIRSET = PIN7_bm;

	USARTC1.BAUDCTRLB = 0;
	USARTC1.BAUDCTRLA = BAUD_PRESCALE;
	
	// Set Control Reg C
	// CMODE = 00 (Async USART)
	// PMODE = 00 (No Parity) (10 = Even, 11 = Odd)
	// SBMODE = 0 (1-Stop) (1 = 2-Stop Bits)
	// CHSIZE = 011 (8bit)
	USARTC1.CTRLC = (USARTC1.CTRLC & ~USART_CHSIZE_gm) | USART_CHSIZE_8BIT_gc;

	// Set Control Reg B
	// Enable Rx and Tx
	USARTC1.CTRLB = (USART_RXEN_bm | USART_TXEN_bm);
	
	USARTC1.CTRLA = USART_RXCINTLVL_HI_gc;
}

void debugPutChar(char c) {
	while (!(USARTC1.STATUS & USART_DREIF_bm));
	USARTC1.DATA = c;
}

char debugGetChar() {
	while (!(USARTC1.STATUS & USART_RXCIF_bm));
	return USARTC1.DATA;
}

void debugSendString(char *s) {
	while (*s) {
		debugPutChar(*s++);
	}
}