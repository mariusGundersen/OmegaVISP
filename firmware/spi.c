#include "spi.h"

void SPI_init(void){
	/* Set MOSI and SCK output, all others input */
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_RESET);
	/* Enable SPI, Master */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1)|(0<<SPR0);
	SPSR = (0<<SPI2X);
	/*
	SPI2X 	SPR1 	SPR0 	SCK Frequency	CLK
	1		0		0 		fosc/2			1
	0		0		0 		fosc/4			2
	1		0		1 		fosc/8			3
	0		0		1 		fosc/16			4
	1		1		0 		fosc/32			5
	0		1		0 		fosc/64			6
	1		1		1 		fosc/64			6
	0		1		1 		fosc/128		7
	*/
}
uint8_t SPI_Tx(uint8_t cData){
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	/* Return the data sent by the slave */
	return SPDR;
}
void ISP_Swap(uint8_t*byte){
	*(byte+0) = SPI_Tx(*(byte+0));
	//_delay_ms(byteDelay);
	*(byte+1) = SPI_Tx(*(byte+1));
	//_delay_ms(byteDelay);
	*(byte+2) = SPI_Tx(*(byte+2));
	//_delay_ms(byteDelay);
	*(byte+3) = SPI_Tx(*(byte+3));
	//_delay_ms(byteDelay);
}
void SPI_clock(uint8_t speed){
	SPSR = (speed % 2)<<SPI2X;

}
