#include "defines.h"
#include <avr/io.h>
#include <util/delay.h>


void SPI_init(void);
uint8_t SPI_Tx(uint8_t cData);
void ISP_Swap(uint8_t*byte);
void SPI_clock(uint8_t speed);
