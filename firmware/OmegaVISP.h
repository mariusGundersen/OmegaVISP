#include "defines.h"
#include "uart.h"
#include "spi.h"
#include <inttypes.h>
#include <avr/io.h>
#include <math.h>



#define STK500    135.63e-9 
#define AVRISP    271.27e-9 
#define B   12.0 
 
volatile uint8_t sequenceNumber; //Current sequence number. Wraps around to 0 when overflows.
volatile uint8_t receiveBuffer[BUFFER_SIZE];




/*FUNCTIONS AND METHODS*/
int main(void);
void sendHeader(uint16_t size);
uint8_t calcSckDur(uint16_t freq);
void readyBusyPolling();
