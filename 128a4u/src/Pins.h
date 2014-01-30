/*
 * Pins.h
 *
 * Created: 19-12-2013 15:23:31
 *  Author: Schriek
 */ 


#ifndef PINS_H_
#define PINS_H_

/* Includes */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

/* Defines */
#define F_CPU 32000000 //Clock snelheid

#ifdef F_CPU
#include <util/delay.h>
#else
#warning "Klok niet gezet"
#endif

#define RTC_MILLISECONDS 10
#define BUTTON_DEBOUNCE_RATE 50
#define INACTIV_TIMEOUT (8 * 60 * 100L) /* 10 minuten */

#define VREFB_VALUE 2.028
#define VREFBAT_VALUE VREFB_VALUE * 3.2
#define VREFBATH_VALUE VREFB_VALUE * 11

/* DHT */
#define DHT_DATA_PIN PIN2_bm
#define DHT_DATA_PORT PORTC /* voor breadbord */

/* ADC gerelateerd (Port A) */
#define ADCA1 ADC_CH_MUXPOS_PIN4_gc
#define ADCA2 ADC_CH_MUXPOS_PIN5_gc
#define ADCA3 ADC_CH_MUXPOS_PIN6_gc
#define ADCA4 ADC_CH_MUXPOS_PIN7_gc

#define ADC_GND ADC_CH_MUXPOS_PIN3_gc
#define VBATTH ADC_CH_MUXPOS_PIN2_gc
#define VBATT ADC_CH_MUXPOS_PIN1_gc
#define VREF ADC_REFSEL_AREFA_gc
 
/* Port B */
#define SEN1_EN PIN3_bm
#define SEN2_EN PIN2_bm
#define HY_EN PIN1_bm
#define VREF_B PIN0_bm

/* Port C */
#define DEBUG_RX PIN7_bm
#define DEBUG_TX PIN6_bm
#define BT_STAT PIN5_bm
#define BT_KEY PIN4_bm
#define BT_EN PIN3_bm
#define C_STAT PIN1_bm
#define USB_STAT PIN0_bm

/* Port D */
#define ON_BUTTON PIN5_bm
#define LIGHT_BUTTON PIN4_bm
#define LED PIN3_bm
#define RED PIN2_bm
#define GREEN PIN1_bm
#define BLUE PIN0_bm

/* Port E */
#define BLDR_EN PIN0_bm
#define POWER_EN PIN1_bm
#define BT_RX PIN2_bm
#define BT_TX PIN3_bm

/* Prototypes */
extern void debugPutChar(char c);

/* Eigen stream gekoppeld aan usart (e.g. printf > usart) */
static FILE mystdout = FDEV_SETUP_STREAM (debugPutChar, NULL, _FDEV_SETUP_WRITE);

#endif /* PINS_H_ */