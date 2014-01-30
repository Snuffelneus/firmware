/*
 * powermanager.h
 *
 * Created: 1/23/2014 9:22:10 PM
 *  Author: rayme_001
 */ 


#ifndef POWERMANAGER_H_
#define POWERMANAGER_H_

#include "Pins.h"
#include "adc.h"
#include "ledHandler.h"
#include "rtc.h"

void powerManagerInit(void);

void powerOn(void);

void powerOff(void);

void powerOnBT(void);

void powerOffBT(void);

void powerOnHeater(void);

void powerOffHeater(void);

#endif /* POWERMANAGER_H_ */