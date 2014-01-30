/*
* sensors.c
*
* Created: 1/24/2014 11:35:31 AM
*  Author: rayme_001
*/

#include "sensors.h"



void measure(void) {
	unsigned long time;
	unsigned long startTime;
	int i;
	
	//RGBShowColor(Green);
	//g = 2000;
	
	reset_rtc();
	
	time = millis();
	startTime = time;
	
	//powerOnHeater();
	
	//while(millis() - startTime < 18000);
	
	// Pulseer
	
	char buffer[80];
	
	int ret = readDHT11();
	
	if(ret == 0) {
		printf("Humidity:\t%d\r\n", humidity);
		printf("Temperature:\t%d\r\n", temperature);
		} else {
		printf("Foute DTH11 meting:\t%d\r\n", ret); // abort meting?
	}
	
	double intBatVolt = readInternalBattery();
	double extBatVolt = readExternalBattery();
	
	double sensor = 0;
	
	for(i = 0; i < 15; i++) {
		sensor += readSensor();
	}
	
	sensor /= i;
	
	printf("ADC's ruw: 1 (%.0f), 2 (%.0f), 3 (%.0f), 4 (%.0f)\r\n", adc1, adc2, adc3, adc4);
	printf("ADC's : 1 (%f), 2 (%f), 3 (%f), 4 (%f)\r\n", ((adc1 * VREFB_VALUE) / 4096), ((adc2 * VREFB_VALUE) / 4096), ((adc3 * VREFB_VALUE) / 4096), ((adc4 * VREFB_VALUE) / 4096));
	printf("VSEN : %f, VRES : %f\r\n", vsen, vres);
	printf("Result : %f\r\n", sensor);
	printf("Accu : %f\r\n", intBatVolt);
	printf("12V Accu : %f\r\n", extBatVolt);
	
	//Format : sensor-warmte-vochtigheid--accu1--accu2-EOM (end of message)
	sprintf(buffer, "Result--%.0f--%d--%d--%f--%f--EOM", sensor, temperature, humidity, intBatVolt, extBatVolt);
	printf("%s\r\n", buffer);
	
	bluetoothSendString(buffer);
	
	powerOffHeater();
	//g = 0;
	RGBShowColor(Blue);
}