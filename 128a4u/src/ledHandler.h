/*
* ledHandler.h
*
* Created: 1/24/2014 8:32:24 AM
*  Author: rayme_001
*/


#ifndef LEDHANDLER_H_
#define LEDHANDLER_H_

#include "pins.h"

#define BLINK_DELAY_MS 1500 //Led blink snelheid

unsigned int r;
unsigned int g;
unsigned int b;

enum LedColor
{
	Red = 0, Green = 1, Blue = 2, Yellow = 3, Pink = 4, Cyaan = 5, White = 6
};

void initializeLedHandler(void);

void RGBShowColor(unsigned int color);

void RGBOff(void);

int pulseLed(unsigned int color, short interval);

void switchFlashLight(void);

void initializePWM(void);

void updatePWM(void);

#endif /* LEDHANDLER_H_ */