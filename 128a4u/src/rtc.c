/*
* rtc.c
*
* Created: 1/24/2014 8:46:12 AM
*  Author: rayme_001
*/

#include "rtc.h"

volatile unsigned long rtc_millis = 0;

/* RTC clock instellen */
void Config32KHzRTC(void)
{
	CCP = CCP_IOREG_gc; //Security Signature to modify clock
	OSC.CTRL |= OSC_RC32KEN_bm; // enable internal 32KHz Osc
	// select RTC clk source
	CLK.RTCCTRL = 0x5;  // internal 32KHz Osc source RTC enable
	RTC.CTRL = CLK_RTCSRC_RCOSC_gc | CLK_RTCEN_bm;     // 1KHz/1024 = 1second/tick

	// wait for RTC SYNC status not busy before returning
	while(RTC.STATUS & RTC_SYNCBUSY_bm);
}

void initializeRTC(void) {
	RTC.PER = RTC_MILLISECONDS-1;                                                // overflow period
	RTC.CNT = 0;
	RTC.COMP = RTC_MILLISECONDS-1;
	RTC.CTRL = RTC_PRESCALER_DIV1_gc;
	RTC.INTCTRL = RTC_COMPINTLVL_HI_gc;
}

/* RTC counter op 0 zetten */
void reset_rtc(void) {
	rtc_millis = 0;
}

/* Het aantal millieseconden sinds het opstarten van de snuffelneus
* Disabled interrupts zodat niet halverwege het lezen de waarde veranderd
* kan worden.
*/
unsigned long millis(void) {
	cli();
	unsigned long result = rtc_millis;
	sei();
	
	return result;
}