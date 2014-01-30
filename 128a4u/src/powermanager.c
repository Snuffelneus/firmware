/*
* powermanager.c
*
* Created: 1/23/2014 9:21:57 PM
*  Author: rayme_001
*/

#include "powermanager.h"




void powerManagerInit(void) {
	PORTE.DIRSET = POWER_EN; // Board
	
	powerOn();
	
	
	//double vBattery = 0;
	//vBattery = readInternalBattery();
	
	/*
	if(vBattery < 3.3)
	{
		RGBShowColor(Red);
		//powerOff();
	}*/
	
	//Set powerPins direction mode
	PORTC.DIRSET = PIN3_bm; // BT
	PORTB.DIRSET = HY_EN; // Heater
}

void powerOn(void) {
	PORTE.OUTSET = POWER_EN;
}

void powerOff(void) {
	PORTE.OUTCLR = POWER_EN;
}

void powerOnBT(void) {
	PORTC.OUTSET = PIN3_bm;
}

void powerOffBT(void) {
	PORTC.OUTCLR = PIN3_bm;
}

void powerOnHeater(void) {
	PORTB.OUTSET = HY_EN;
	RGBShowColor(Yellow);
	printf("Heating\r\n");
	HeaterMillis = millis();
}

void powerOffHeater(void) {
	PORTB.OUTCLR = HY_EN;
	printf("Power off heater\r\n");
	RGBShowColor(Green);
}