/************************************************************************/
/* Includes  & Defines                                                  */
/************************************************************************/
#include "Pins.h"
#include "DHT11.h"
#include "powermanager.h"
#include "bluetooth.h"
#include "debug.h"
#include "ledHandler.h"
#include "rtc.h"
#include "adc.h"

/************************************************************************/
/* Prototypes                                                           */
/************************************************************************/
void clock_init(void);
int isUsbConnected(void);

/* Kijken of USB verbonden is (werkt niet :D) */
int isUsbConnected(void) {
	return PORTC.IN & USB_STAT;
}

/* Timer compare interrupt port D 0 */
ISR(TCD0_CCA_vect) {
	updatePWM();
}

/* RTC compare interrupt */
ISR(RTC_COMP_vect) {
	if(++rtc_millis >= INACTIV_TIMEOUT) {
		powerOff();
	}
	
	
	if(heaterOn == 1){
		if(millis() - HeaterMillis >= HeatUpTime)
		{
			heaterOn = 0;
			powerOffHeater();
			measure();
		}
	}
}

/* Led knop interrupt */
ISR(PORTD_INT0_vect) {
	static unsigned long last_interrupt = 0;
	unsigned long now = millis();
	
	if(now - last_interrupt > BUTTON_DEBOUNCE_RATE) {
		PORTD.OUTTGL = LED;
	}
	
	last_interrupt = now;
}

/*
* Interrupt routine usartC1 RX
*/
ISR(USARTC1_RXC_vect) {
	char c = USARTC1.DATA;
	//printf("PORTC %c ", c);
	
	if(c == 0x0D) { //Return, werkt met Putty, werkt niet met hyperterminal
		store_char('\0', &rx_buffer_c1); //null terminate voor strcmp
		handleMessage(&rx_buffer_c1);
		} else {
		store_char(c, &rx_buffer_c1);
	}
}

/*
* Interrupt routine usartE0 RX
*/
ISR(USARTE0_RXC_vect) {
	/* Resultaten die de HC06 terug geeft zijn niet null terminated of dergelijken, ToDo'tje  */
	
	char c = USARTE0.DATA;
	printf("%c", c);
	
	if(c == '\n') {
		store_char('\0', &rx_buffer_e0); //null terminate voor strcmp
		handleMessage(&rx_buffer_e0);
		} else {
		store_char(c, &rx_buffer_e0);
	}
}

/*
* Clock instellingen
*/
void clock_init(void) {
	CCP = CCP_IOREG_gc;              // disable register security for oscillator update
	OSC.CTRL = OSC_RC32MEN_bm;       // enable 32MHz oscillator
	while(!(OSC.STATUS & OSC_RC32MRDY_bm)); // wait for oscillator to be ready
	CCP = CCP_IOREG_gc;              // disable register security for clock update
	CLK.CTRL = CLK_SCLKSEL_RC32M_gc; // switch to 32MHz clock
}

int main (void)
{
	double batteryLevel;
	heaterOn = 0;
	
	//Power on device, check internal battery
	powerManagerInit(); // initialise power manager + turn power on
	powerOffHeater();
	
	clock_init();
			
	initializeADC();
	
	initializeLedHandler();
	RGBOff();
	RGBShowColor(Blue);
	
	batteryLevel = readInternalBattery();

	
	//if(batteryLevel < 3.3)
	//{
		//RGBShowColor(Red);
		//_delay_ms(500);
		//RGBOff();
		//_delay_ms(500);
		//RGBShowColor(Red);
		//_delay_ms(500);
		//
		////powerOff();
		//
		//return 0;
	//}
	
	Config32KHzRTC(); //Todo:  RTC ook echt om de 1ms en niet wat die nu doet...
	
	initializeRTC();
	InitializeDebug();
	initializeBluetooth();
	
	/* DHT11 enable */
	PORTB.DIRSET = SEN1_EN;
	PORTB.OUTSET = SEN1_EN;
	
	/* Sen 2 */
	PORTB.DIRSET = SEN2_EN;
	PORTB.OUTSET = SEN2_EN;
	
	/* USB status */
	PORTC.DIRCLR = USB_STAT;
	
	
	//initializePWM();
	
	stdout = &mystdout;																	/* onze eigen stdout gebruiken (usart) */
	
	sei();																				/* Interrupts enablen */
	
	PMIC.CTRL |= (PMIC_HILVLEN_bm | PMIC_LOLVLEN_bm);										/* Hi en Lo lvl interrupts */
	
	/* BT config */
	PORTC.DIRCLR = BT_STAT;
	
	PORTC.DIRSET = BT_KEY;
	PORTC.OUTCLR = BT_KEY;
	
	PORTC.DIRSET = BT_EN;
	PORTC.OUTSET = BT_EN;
	
	PORTB.DIRSET = HY_EN;
	//PORTB.OUTSET = HY_EN;
	
	bluetoothRename("snuffelneusWit");
	
	//usartE0_sendstring("AT+NAMEsnuffelneus6.0");
	
	_delay_ms(2000);

	while(1) {
	}
}