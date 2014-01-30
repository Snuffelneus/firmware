/*
* bluetooth.c
*
* Created: 1/23/2014 9:31:40 PM
*  Author: rayme_001
*/

#include "bluetooth.h"

ring_buffer rx_buffer_e0 = { { 0 }, 0, 0 };

void initializeBluetooth(void) {
	powerOnBT();
	
	// Set Tx pin to an output
	PORTE.DIRSET = PIN3_bm;

	USARTE0.BAUDCTRLB = 0;
	USARTE0.BAUDCTRLA = BAUD_PRESCALE;
	
	// Set Control Reg C
	// CMODE = 00 (Async USART)
	// PMODE = 00 (No Parity) (10 = Even, 11 = Odd)
	// SBMODE = 0 (1-Stop) (1 = 2-Stop Bits)
	// CHSIZE = 011 (8bit)
	USARTE0.CTRLC = (USARTE0.CTRLC & ~USART_CHSIZE_gm) | USART_CHSIZE_8BIT_gc;

	// Set Control Reg B
	// Enable Rx and Tx
	USARTE0.CTRLB = (USART_RXEN_bm | USART_TXEN_bm);
	
	// Setup interrupt?
	USARTE0.CTRLA = USART_RXCINTLVL_HI_gc;
}

void bluetoothPutChar(char c) {
	while (!(USARTE0.STATUS & USART_DREIF_bm));
	USARTE0.DATA = c;
}

char bluetoothGetChar() {
	while (!(USARTE0.STATUS & USART_RXCIF_bm));
	return USARTE0.DATA;
}

void bluetoothSendString(char *s) {
	while (*s) {
		bluetoothPutChar(*s++);
	}
}

void handleMessage(ring_buffer *ring) {
	char msg[80];
	
	char* curr = strtok(ring->buffer, "-");
	int action = -1;

	while (curr) {
		if (action == -1) {
			if (!strcmp(curr, "wakeup")) {
				printf("wakeup ack\r\n");
				
				RGBShowColor(Yellow);
				heaterOn = 1;
				powerOnHeater();
				
				break;
			} else if (!strcmp(curr, "shutdown")) {
				printf("shutdown ack\r\n");
				
				powerOff();
				break;
				
			} else if (!strcmp(curr, "setname")) {
				printf("setname ack\r\n");
				
				action = 5;
			} else {
				switch (action) {
					case 5:
					printf("eede\r\n");
					sprintf(msg, "AT+NAME%s", curr);
					bluetoothSendString(msg);
					
					break;
					
					default:

					break;
				}
			}

			curr = strtok(NULL, " ");
		}
	}
	
	/* reset buffer */
	memset(ring->buffer, 0, sizeof(ring->buffer));
	ring->head = 0;
	ring->tail = 0;
}

void bluetoothRename(char *s) {
	bluetoothSendString("AT+NAME");
	bluetoothSendString(s);
}