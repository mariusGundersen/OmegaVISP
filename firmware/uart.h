#include "defines.h"
#include <inttypes.h>

void UART_init(void);
void UART_Tx(unsigned char);
void UART_Tx_ASCII(uint8_t);
void UART_Tx_String(uint8_t*, uint8_t);
uint8_t UART_Rx(void);
uint8_t UART_Tx_Checksum(uint8_t byte, uint8_t send);
uint8_t UART_Rx_Checksum(uint8_t send);
 
 
 
#define USE_2X false
//Set this to your chips frequency
//#define F_CPU 4000000
