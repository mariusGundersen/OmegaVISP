#include "uartcommand.h"
#include "spicommand.h"
#include <avr/io.h>
/*
int main(void) is in AVR068.h

Based on: 
AVR069 (http://www.atmel.com/dyn/resources/prod_documents/doc8015.pdf)
AVR910 (http://www.atmel.com/dyn/resources/prod_documents/DOC0943.PDF)

Features:
[OK] Connect to AVRstudio 4
[OK] Start and leave programming mode
[OK] Read signature
[OK] Read fuses
[OK] Write fuses
[OK] Read flash
[OK] Write flash
[OK] Read lockbits
[OK] Write lockbits
[  ] Read eeprom
[  ] Write eeprom
[OK] Erase chip
[OK] Calibrate RC-Oscillator
[  ] Set ISP-frequency

*/


#define putPin(pin, reg, val)	(val ? setPin(pin, reg) : clrPin(pin, reg))
#define setPin(pin, reg)		((reg)|(1<<(pin)))
#define clrPin(pin, reg)		((reg)&(~(1<<(pin))))
#define getPin(pin, reg)		(((reg)>>(pin))&1)

/* CPU frequency */
#define F_CPU 					7370000UL
#define T_STK500    			135.63e-9 
#define T_AVRISP    			271.27e-9 
#define B   					12.0 
 
/* UART baud rate */
#define BAUD  					115200

/* Constants */
#define BUFFER_SIZE 			275

/* ISP pins */
#define DDR_SPI	 				DDRB
#define DD_RESET				4
#define DD_MOSI					5
#define DD_MISO 				6
#define DD_SCK					7


volatile uint8_t byteDelay;
