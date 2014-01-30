/*
 * BT.h
 *
 * Created: 1/23/2014 9:31:23 PM
 *  Author: rayme_001
 */ 


#ifndef BT_H_
#define BT_H_

#include "powermanager.h"
#include "pins.h"
#include "uart.h"
#include "sensors.h"
#include "rtc.h"

ring_buffer rx_buffer_e0;

void initializeBluetooth(void);

/*
* Character printen (@see printf)
*/
void bluetoothPutChar(char c);

/*
* Leest een character als er een in het register staat (blokeerd zo lang het leeg is)
*/
char bluetoothGetChar(void);

/*
* Beter printf gebruiken
*/
void bluetoothSendString(char *s);

void bluetoothRename(char *s);

void handleMessage(ring_buffer *ring);

#endif /* BT_H_ */