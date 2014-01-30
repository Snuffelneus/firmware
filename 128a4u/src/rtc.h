/*
 * rtc.h
 *
 * Created: 1/24/2014 8:46:01 AM
 *  Author: rayme_001
 */ 


#ifndef RTC_H_
#define RTC_H_

#define HeatUpTime 1000 //Sec

#include "pins.h"

volatile unsigned long rtc_millis;
unsigned long HeaterMillis;
int heaterOn;

/* RTC clock instellen */
void Config32KHzRTC(void);

void initializeRTC(void);

void reset_rtc(void);

unsigned long millis(void);

#endif /* RTC_H_ */