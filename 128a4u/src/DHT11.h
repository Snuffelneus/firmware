/*
 * DHT11.h
 *
 * Created: 19-12-2013 14:27:15
 *  Author: Schriek
 */ 


#ifndef DHT11_H_
#define DHT11_H_

#include "Pins.h"

#define DHT_TIMEOUT 1000

#define DTH_FAIL_1 1
#define DTH_FAIL_2 2
#define DTH_FAIL_3 3

int readDHT11(void);

int humidity;
int temperature;

#endif /* DHT11_H_ */