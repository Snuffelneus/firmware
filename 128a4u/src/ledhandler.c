
/*
* ledHandler.c
*
* Created: 21-11-2013 15:27:15
* Author: Björn Braber
*/
#include "ledHandler.h"

unsigned int r = 0;
unsigned int g = 0;
unsigned int b = 0;
unsigned int direction = 1;

void initializeLedHandler(void)
{
	//Led knop
	PORTD.DIRCLR = LIGHT_BUTTON;
	
	// init leds
	PORTD.DIRSET = LED;
	PORTD.DIRSET = RED;
	PORTD.DIRSET = GREEN;
	PORTD.DIRSET = BLUE;
	
	/* Led button interrupt */
	PORTD.PIN0CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc;
	PORTD.INT0MASK = LIGHT_BUTTON;
	PORTD.INTCTRL = PORT_INT0LVL_LO_gc;
}

void RGBShowColor(unsigned int color)
{
	PORTD.OUTSET = RED | GREEN | BLUE;
	
	switch (color)
	{
		case Red:
		PORTD.OUTCLR = RED;
		break;
		case Green:
		PORTD.OUTCLR = GREEN;
		break;
		case Blue:
		PORTD.OUTCLR = BLUE;
		break;
		case Yellow:
		PORTD.OUTCLR = RED | GREEN;
		break;
		case Pink:
		PORTD.OUTCLR = RED | BLUE;
		break;
		case Cyaan:
		PORTD.OUTCLR = GREEN | BLUE;
		break;
		default:
		break;
	}
}

void RGBOff(void)
{
	PORTD.OUTSET = RED | GREEN | BLUE;
}

int pulseLed(unsigned int color, short interval)
{
	return 1;
}

void switchFlashLight(void)
{
	if(PORTD.OUT & LED)
	{
		PORTD.OUTCLR = LED;
	}
	else
	{
		PORTD.OUTSET = LED;
	}
}

void initializePWM(void) {
	/* 0 */
	TCD0.INTCTRLB = TC_CCAINTLVL_LO_gc;
	TCD0.CTRLA = TC_CLKSEL_DIV1_gc;
	TCD0.CTRLB = TC0_CCAEN_bm | TC0_CCBEN_bm | TC0_CCCEN_bm| TC0_WGMODE1_bm | TC0_WGMODE0_bm;

	TCD0.PER = 2000 - 1;
	TCD0.CCA = 2000;
	TCD0.CCB = 2000;
	TCD0.CCC = 2000;
	TCD0.CNT = 0;
}

void updatePWM(void) {
	if(b <= 2000 && direction) {
		if(++b == 2000) {
			direction = 0;
		}
	} else {
		if(--b == 0) {
			direction = 1;
		}
	}

	_delay_us(500);
	TCD0.CCA = 2000 - b;
	TCD0.CCB = 2000 - g;
	TCD0.CCC = 2000 - r;
}