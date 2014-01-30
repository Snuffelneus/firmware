/*
 * adc.h
 *
 * Created: 1/24/2014 9:33:08 AM
 *  Author: rayme_001
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "pins.h"

#define TOP 4095
#define CALCULATE_VBATT(I) (double) ((I * VREFBAT_VALUE) / TOP)
#define CALCULATE_VBATTH(I) (double) ((I * VREFBATH_VALUE) / TOP)
#define CALCULATE_ADC(I, J) (double) (((I -J) * VREFB_VALUE) / TOP)
#define CALCULATE_RSEN(VRES, VSEN) (double) (VSEN / (VRES / 5360))

double adc1, adc2, adc3, adc4, vres, vsen;

int gADC_CH0_ZeroOffset;

void initializeADC(void);

void calculateGroundOffset(void);

double readInternalBattery(void);

double readExternalBattery(void);

double readSensor(void);

uint8_t ReadCalibrationByte(uint8_t index);

#endif /* ADC_H_ */