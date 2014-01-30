/*
* DHT11.c
*
* Created: 19-12-2013 14:26:15
*  Author: Schriek
*/

#include "DHT11.h"

int readDHT11(void)
{
	uint8_t bits[5];
	uint8_t i,j = 0;

	memset(bits, 0, sizeof(bits));

	//reset port
	DHT_DATA_PORT.DIRSET= DHT_DATA_PIN;
	DHT_DATA_PORT.OUTSET = DHT_DATA_PIN;
	
	_delay_ms(200);

	//send request
	DHT_DATA_PORT.DIRSET= DHT_DATA_PIN;
	DHT_DATA_PORT.OUTCLR = DHT_DATA_PIN;
	_delay_ms(18);
	DHT_DATA_PORT.OUTSET = DHT_DATA_PIN;
	_delay_us(40);
	DHT_DATA_PORT.DIRCLR= DHT_DATA_PIN;

	// ACKNOWLEDGE or TIMEOUT
	unsigned int loopCnt = 10000;
	while(!(DHT_DATA_PORT.IN & DHT_DATA_PIN))
	if (loopCnt-- == 0) return DTH_FAIL_1;

	loopCnt = 10000;
	while((DHT_DATA_PORT.IN & DHT_DATA_PIN))
	if (loopCnt-- == 0) return DTH_FAIL_1;

	//read the data
	uint16_t timeoutcounter = 0;
	for (j=0; j<5; j++) { //read 5 byte
		uint8_t result=0;
		for(i=0; i<8; i++) {//read every bit
			timeoutcounter = 0;
			while(!(DHT_DATA_PORT.IN & DHT_DATA_PIN)) { //wait for an high input (non blocking)
				timeoutcounter++;
				if(timeoutcounter > DHT_TIMEOUT) {
					return DTH_FAIL_2; //timeout
				}
			}
			
			_delay_us(30);
			if(DHT_DATA_PORT.IN & DHT_DATA_PIN) //if input is high after 30 us, get result
			result |= (1<<(7-i));
			timeoutcounter = 0;
			while(DHT_DATA_PORT.IN & DHT_DATA_PIN) { //wait until input get low (non blocking)
				timeoutcounter++;
				if(timeoutcounter > DHT_TIMEOUT) {
					return DTH_FAIL_3; //timeout
				}
			}
		}
		
		bits[j] = result;
	}
	
	if ((uint8_t)(bits[0] + bits[1] + bits[2] + bits[3]) == bits[4]) { //Checksum
		//return temperature and humidity
		temperature = bits[2];
		humidity = bits[0];
		
		return 0;
	}
	
	return -1;
}