/*
 * debug.h
 *
 * Created: 1/23/2014 9:45:00 PM
 *  Author: rayme_001
 */ 


#ifndef DEBUG_H_
#define DEBUG_H_

#include "powermanager.h"
#include "pins.h"
#include "uart.h"

ring_buffer rx_buffer_c1;

void InitializeDebug(void);

/*
* Character printen (@see printf)
*/
void debugPutChar(char c);

/*
* Leest een character als er een in het register staat (blokeerd zo lang het leeg is)
*/
char debugGetChar(void);

/*
* Beter printf gebruiken
*/
void debugSendString(char *s);

#endif /* DEBUG_H_ */