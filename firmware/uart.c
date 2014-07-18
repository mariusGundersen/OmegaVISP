#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include "uart.h"
 
 
 
 
/*****************************************************************************
*
*   Function name : UART_init
*
*   Returns :       None
*
*   Parameters :    None
*
*   Purpose :       Initiate the UART
*
*****************************************************************************/
void UART_init(void){
   //#define BAUD 9600
   #include <util/setbaud.h>
   UBRRHI = UBRRH_VALUE;
   UBRR = UBRRL_VALUE;
   #if USE_2X
   UCSRA |= (1 << U2X);
   #else
   UCSRA &= ~(1 << U2X);
   #endif
   //Enable Receiving, transmitting and enable receive interupt.
   UCSRB = (1<<RXEN)|(1<<TXEN)|(0<<RXCIE)|(0<<UDRIE);
   // Async. mode, 8N1
   //UCSRC = (0<<UMSEL)|(0<<UPM1)|(0<<UPM0)|(0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0)|(0<<UCPOL);
}
 
 
 
/*****************************************************************************
*
*   Function name : UART_Tx
*
*   Returns :       None
*
*   Parameters :    char data: byte to send
*
*   Purpose :       Send one byte through the UART
*
*****************************************************************************/
void UART_Tx(uint8_t data)
{
    while (!(UCSRA & (1<<UDRE)));
    UDR = data;
}
 
 
/*****************************************************************************
*
*   Function name : UART_Rx
*
*   Returns :       char: byte received
*
*   Parameters :    None
*
*   Purpose :       Receives one byte from the UART
*
*****************************************************************************/
uint8_t UART_Rx(void)
{
    while (!(UCSRA & (1<<RXC)));
    return UDR;
}
 
/*****************************************************************************
*
*   Function name : UART_Tx_ASCII
*
*   Returns :       None
*
*   Parameters :    uint8_t data: data to send
*
*   Purpose :       Sends a number through the USART according to ASCII
*
*****************************************************************************/
void UART_Tx_ASCII(uint8_t data){
	uint8_t output[3] = {0,0,0};
 
	output[2] = data%10;
	data = data/10;
	output[1] = data%10;
	data = data/10;
	output[0] = data%10;
 
	UART_Tx(output[0]+48);
	UART_Tx(output[1]+48);
	UART_Tx(output[2]+48);
 
 
}


 /*****************************************************************************
*
*   Function name : UART_Tx_String
*
*   Returns :       None
*
*   Parameters :    uint8_t* data: data to send
*					uint8_t length: length of data
*
*   Purpose :       Sends a string through the UART
*
*****************************************************************************/
void UART_Tx_String(uint8_t *data, uint8_t length){
	uint8_t i=0; 
	for(i=0; i<length; i++){
		UART_Tx_Checksum(data[i], 0);
	}
 
}


 /*****************************************************************************
*
*   Function name : UART_Tx_Checksum
*
*   Returns :       None
*
*   Parameters :    uint8_t byte: data to send
*					uint8_t send: Send checksum
*
*   Purpose :       Sends the byte on the uart, and updates the checksum
*					If send != 0, the checksum is sent instead, and then it is reset;
*
*****************************************************************************/



uint8_t UART_Tx_Checksum(uint8_t byte, uint8_t send){
	static uint8_t checksum = 0;
	if(send != 0){
		UART_Tx(checksum);
		checksum = 0;
	}else{
		checksum^=byte;
		UART_Tx(byte);
	}
	return checksum;
}


 /*****************************************************************************
*
*   Function name : UART_Rx_Checksum
*
*   Returns :       uint8_t byte received
*
*   Parameters :    uint8_t send: Send checksum
*
*   Purpose :       Receive the byte on the uart, and updates the checksum
*					If send != 0, the checksum is sent instead, and then it is reset;
*
*****************************************************************************/


uint8_t UART_Rx_Checksum(uint8_t send){
	static uint8_t checksum = 0;
	uint8_t data;
	if(send == 0){
		data = UART_Rx();
		checksum ^= data;
	}else{
		data = checksum;
		checksum = 0;
	}
	return data;
}
