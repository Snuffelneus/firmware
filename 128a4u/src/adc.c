/*
* adc.c
*
* Created: 1/24/2014 9:30:11 AM
*  Author: rayme_001
*/

#include "adc.h"

void initializeADC(void) {
	ADCA.CALL = ReadCalibrationByte( offsetof(NVM_PROD_SIGNATURES_t, ADCACAL0) );  /* Calibratie */
	ADCA.CALH = ReadCalibrationByte( offsetof(NVM_PROD_SIGNATURES_t, ADCACAL1) );
	
	/* ADC pin config, is dit nodig? */
	PORTA.DIRCLR = VBATT | VBATTH | ADCA1 | ADCA2 | ADCA3 | ADCA4;
	
	/*ADC init*/
	ADCA.CTRLA |= 0x1;																	/* enable ADC */
	ADCA.CTRLB = ADC_RESOLUTION_12BIT_gc;												/* 12 bit unsigned conversie */
	ADCA.REFCTRL = ADC_REFSEL_AREFB_gc;													/* referentie spanning port B:0 */
	
	// calculate ground offset call
	calculateGroundOffset();
	
	ADCA.PRESCALER = ADC_PRESCALER_DIV64_gc;		// set prescaler
	
	ADCA.CH0.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc;
	ADCA.CH1.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc;
	ADCA.CH2.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc;
	ADCA.CH3.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc;
	
	ADCA.CH0.MUXCTRL = VBATT; // pin 0 kleine battery
	ADCA.CH1.MUXCTRL = VBATTH; // pin 1 kleine
	
	_delay_us(2);
}

void calculateGroundOffset(void) {
	/*Calculate ground offset*/

	ADCA.PRESCALER = ADC_PRESCALER_DIV32_gc;											/* Prescaler */
	ADCA.CH0.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc;									/* Single ended mode */
	ADCA.CH0.MUXCTRL = ADC_GND;															/* port A:4 is onze positieve in */
	_delay_us(2); /* Laten stabiliseren */

	ADCA.CH0.CTRL |= ADC_CH_START_bm;
	//ADCA.CTRLA |= 0x4;																	/* Single conversion */

	while(!ADCA.CH0.INTFLAGS);															/* wait for conversion complete flag */
	ADCA.CH0.INTFLAGS = ADC_CH_CHIF_bm;
	gADC_CH0_ZeroOffset = ADCA.CH0RES;
}

double readInternalBattery(void) {
	/* Read small battery*/
	double v_vbatt, vbatt;
	
	ADCA.CH0.CTRL |= ADC_CH_START_bm;
	
	while(!ADCA.CH0.INTFLAGS);															/* wait for conversion complete flag */
	
	ADCA.CH0.INTFLAGS =  ADC_CH_CHIF_bm;
	
	v_vbatt = (double) ADCA.CH0RES - gADC_CH0_ZeroOffset;
	
	vbatt = CALCULATE_VBATT(v_vbatt); //VBAT
	return vbatt;
	//printf("Accu : %.0f, %f\r\n", v_vbatt, vbatt);
}

double readExternalBattery(void) {
	/* Read big battery */
	double v_vbatth, vbatth;
	
	ADCA.CH1.CTRL |= ADC_CH_START_bm;
	
	while(!ADCA.CH1.INTFLAGS);															/* wait for conversion complete flag */
	ADCA.CH1.INTFLAGS = ADC_CH_CHIF_bm;
	v_vbatth = (double) ADCA.CH1RES - gADC_CH0_ZeroOffset;
	
	vbatth = CALCULATE_VBATTH(v_vbatth); //VBATTH
	return vbatth;
	//printf("12V Accu : %.0f, %f\r\n", v_vbatth, vbatth);
}

double readSensor(void) {
	double res;

	ADCA.CH2.MUXCTRL = ADCA1; // set pin 1 sensor
	ADCA.CH3.MUXCTRL = ADCA2; // set pin 2 sensor
	
	ADCA.CH2.CTRL |= ADC_CH_START_bm; // start reading
	ADCA.CH3.CTRL |= ADC_CH_START_bm; // start reading
	
	while(!ADCA.CH2.INTFLAGS);														/* wait for conversion complete flag */
	ADCA.CH2.INTFLAGS=ADC_CH_CHIF_bm;
	adc1 = (double) ADCA.CH2RES - gADC_CH0_ZeroOffset;
	
	while(!ADCA.CH3.INTFLAGS);														/* wait for conversion complete flag */
	ADCA.CH3.INTFLAGS=ADC_CH_CHIF_bm;
	adc2 = (double) ADCA.CH3RES - gADC_CH0_ZeroOffset;
	
	ADCA.CH2.MUXCTRL = ADCA3; // change pin 1
	ADCA.CH3.MUXCTRL = ADCA4; // change pin 2
	
	ADCA.CH2.CTRL |= ADC_CH_START_bm; // read pin 1 again
	ADCA.CH3.CTRL |= ADC_CH_START_bm; // read pin 2 again
	
	while(!ADCA.CH2.INTFLAGS);
	ADCA.CH2.INTFLAGS=ADC_CH_CHIF_bm;
	adc3 = (double) ADCA.CH2RES - gADC_CH0_ZeroOffset;
	
	while(!ADCA.CH3.INTFLAGS);
	ADCA.CH3.INTFLAGS=ADC_CH_CHIF_bm;
	adc4 = (double) ADCA.CH3RES - gADC_CH0_ZeroOffset;
	
	vsen = CALCULATE_ADC(adc1, adc2);// + 0.0095;
	vres = CALCULATE_ADC(adc4, adc3);// + 0.0098;
	res = CALCULATE_RSEN(vres, vsen);
	
	return res;
}

uint8_t ReadCalibrationByte(uint8_t index)
{
	uint8_t result;

	/* Load the NVM Command register to read the calibration row. */
	NVM_CMD = NVM_CMD_READ_CALIB_ROW_gc;
	result = pgm_read_byte(index);

	/* Clean up NVM Command register. */
	NVM_CMD = NVM_CMD_NO_OPERATION_gc;

	return result;
}