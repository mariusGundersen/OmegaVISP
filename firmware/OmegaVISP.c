#include "OmegaVISP.h"
#include <util/delay.h>

volatile uint8_t sequenceNumber = 1; //Current sequence number. Wraps around to 0 when overflows.
volatile uint8_t receiveBuffer[BUFFER_SIZE];
volatile uint8_t byteDelay = 0;
int main(void){
	uint16_t messageSize = 0;
	uint16_t receiveSize = 0;
	uint8_t byte[4];
	DDRC = 0xff;
	PORTC = 0xff;
	UART_init();
	SPI_init();
	//Status variables
	uint8_t status = 0;//Counter controlled by AVRStudio. This is incremented all the time. If the stk is reset, so is this number.
	uint8_t reset = 0; //What should the reset polarity be, 1 or 0?
	uint32_t address = 0; //Address of byte to be read or written
	uint8_t readMem = 0;
	uint8_t writeMem = 0;
	//_delay_ms(1000.0);
	//UART_Tx_String("OmegaVISP USB", 13);

	/*UART_Tx(0x15);
	PORTB = (1<<DD_RESET);

	byte0 = PROGRAMMING_ENABLE_0;
	byte1 = PROGRAMMING_ENABLE_1;
	byte2 = 0;
	byte3 = 0;
	byte0 = SPI_Tx(byte0);//ISP_Swap(&byte0, &byte1, &byte2, &byte3);
	UART_Tx(byte3);

	PORTC= ~1;
	byte0 = READ_DEVICE_CODE;
	byte1 = 0;
	byte2 = 0;
	byte3 = 0;
	ISP_Swap(&byte0, &byte1, &byte2, &byte3);
	UART_Tx(byte3);

	PORTC= ~2;
	byte0 = READ_DEVICE_CODE;
	byte1 = 0;
	byte2 = 1;
	byte3 = 0;
	ISP_Swap(&byte0, &byte1, &byte2, &byte3);
	UART_Tx(byte3);

	PORTC= ~4;
	byte0 = READ_DEVICE_CODE;
	byte1 = 0;
	byte2 = 2;
	byte3 = 0;
	ISP_Swap(&byte0, &byte1, &byte2, &byte3);
	UART_Tx(byte3);
	while(1);
	*/
	
	
	
	
	while(1){
		UART_Rx_Checksum(1);
		if(UART_Rx_Checksum(0) != MESSAGE_START) continue;
		sequenceNumber = UART_Rx_Checksum(0);
		messageSize = UART_Rx_Checksum(0)<<8;
		messageSize|= UART_Rx_Checksum(0);
		if(UART_Rx_Checksum(0) != TOKEN) continue;
		receiveSize = 0;
		while(receiveSize<messageSize){
			receiveBuffer[receiveSize++] = UART_Rx_Checksum(0);
		}
		if(UART_Rx_Checksum(1) != UART_Rx_Checksum(0)){
			sendHeader(2);
			UART_Tx_Checksum(ANSWER_CKSUM_ERROR, 0);
			UART_Tx_Checksum(ANSWER_CKSUM_ERROR, 0);
			UART_Tx_Checksum(0,1);
			continue;
		}


		uint16_t len;
		uint16_t i;

		switch(receiveBuffer[0]){


			case CMD_SIGN_ON: 	
				sendHeader(11);
				UART_Tx_Checksum(CMD_SIGN_ON, 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(0x08, 0);
				UART_Tx_String((uint8_t*) &REPLY_CMD_SIGNON, 8);
				UART_Tx_Checksum(0,1);
				break;


			case CMD_GET_PARAMETER:
				if(receiveBuffer[1] == PARAM_HW_VER){
					sendHeader(3);
					UART_Tx_Checksum(CMD_GET_PARAMETER, 0);
					UART_Tx_Checksum(STATUS_CMD_OK, 0);
					UART_Tx_Checksum(0x01, 0);


				}else if(receiveBuffer[1] == PARAM_SW_MAJOR){
					sendHeader(3);
					UART_Tx_Checksum(CMD_GET_PARAMETER, 0);
					UART_Tx_Checksum(STATUS_CMD_OK, 0);
					UART_Tx_Checksum(0x02, 0);


				}else if(receiveBuffer[1] == PARAM_SW_MINOR){
					sendHeader(3);
					UART_Tx_Checksum(CMD_GET_PARAMETER, 0);
					UART_Tx_Checksum(STATUS_CMD_OK, 0);
					UART_Tx_Checksum(0x0A, 0);


				}else if(receiveBuffer[1] == PARAM_TOPCARD_DETECT){
					sendHeader(3);
					UART_Tx_Checksum(CMD_GET_PARAMETER, 0);
					UART_Tx_Checksum(STATUS_CMD_OK, 0);
					UART_Tx_Checksum(0xFF, 0);


				}else if(receiveBuffer[1] == PARAM_SCK_DURATION){
					sendHeader(3);
					UART_Tx_Checksum(CMD_GET_PARAMETER, 0);
					UART_Tx_Checksum(STATUS_CMD_OK, 0);
					UART_Tx_Checksum(calcSckDur((uint16_t) F_CPU), 0);


				}else if(receiveBuffer[1] == PARAM_CONTROLLER_INIT){
					sendHeader(3);
					UART_Tx_Checksum(CMD_GET_PARAMETER, 0);
					UART_Tx_Checksum(STATUS_CMD_OK, 0);
					UART_Tx_Checksum(status, 0);


				}else{
					sendHeader(2);
					UART_Tx_Checksum(CMD_GET_PARAMETER, 0);
					UART_Tx_Checksum(STATUS_CMD_FAILED, 0);
				}
					UART_Tx_Checksum(0,1);
				break;


			case CMD_SET_PARAMETER:
				if(receiveBuffer[1] == PARAM_HW_VER){


				}else if(receiveBuffer[1] == PARAM_SW_MAJOR){


				}else if(receiveBuffer[1] == PARAM_SW_MINOR){


				}else if(receiveBuffer[1] == PARAM_TOPCARD_DETECT){


				}else if(receiveBuffer[1] == PARAM_RESET_POLARITY){
					reset = !receiveBuffer[2];

				}else if(receiveBuffer[1] == PARAM_SCK_DURATION){


				}else if(receiveBuffer[1] == PARAM_CONTROLLER_INIT){
					status = receiveBuffer[2];

				}else{
					sendHeader(2);
					UART_Tx_Checksum(CMD_SET_PARAMETER, 0);
					UART_Tx_Checksum(STATUS_CMD_FAILED, 0);
					UART_Tx_Checksum(0,1);
					break;
				}
				sendHeader(2);
				UART_Tx_Checksum(CMD_SET_PARAMETER, 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(0,1);
				break;


			case CMD_ENTER_PROGMODE_ISP: 
				PORTB = reset ? setPin(DD_RESET, PORTB) : clrPin(DD_RESET, PORTB);
				_delay_ms(receiveBuffer[3]);//Wait for pins to stabilize

				byteDelay = receiveBuffer[5];

				byte[0] = PROGRAMMING_ENABLE_0;
				byte[1] = PROGRAMMING_ENABLE_1;
				byte[2] = 0;
				byte[3] = 0;
				ISP_Swap((uint8_t*) &byte);

				sendHeader(2);
				UART_Tx_Checksum(CMD_ENTER_PROGMODE_ISP, 0);
				UART_Tx_Checksum(byte[2] == PROGRAMMING_ENABLE_1 ? STATUS_CMD_OK : STATUS_CMD_FAILED, 0);
				UART_Tx_Checksum(0,1);
				break;


			case CMD_READ_SIGNATURE_ISP: 
				PORTC = 0xf0;
				byte[0] = READ_DEVICE_CODE;
				byte[1] = 5;
				byte[2] = receiveBuffer[4];
				byte[3] = 15;//receiveBuffer[4] == 0 ? 0x1E : (receiveBuffer[4] == 1 ? 0x94 : 0x06);
				ISP_Swap((uint8_t*) &byte);
				sendHeader(4);
				UART_Tx_Checksum(CMD_READ_SIGNATURE_ISP, 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(byte[3], 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(0,1);
				break;


			case CMD_READ_FUSE_ISP: 
				PORTC = 0xf0;
				byte[0] = receiveBuffer[2];
				byte[1] = receiveBuffer[3];
				byte[2] = 0;
				byte[3] = 0;
				ISP_Swap((uint8_t*) &byte);
				sendHeader(4);
				UART_Tx_Checksum(CMD_READ_FUSE_ISP, 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(byte[receiveBuffer[1]-1], 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(0,1);
				break;


			case CMD_PROGRAM_FUSE_ISP: 
				PORTC = 0xf0;
				byte[0] = receiveBuffer[1];
				byte[1] = receiveBuffer[2];
				byte[2] = receiveBuffer[3];
				byte[3] = receiveBuffer[4];
				ISP_Swap((uint8_t*) &byte);
				sendHeader(3);
				UART_Tx_Checksum(CMD_PROGRAM_FUSE_ISP, 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(0,1);
				break;

			case CMD_READ_LOCK_ISP:
				byte[0] = READ_LOCK_BIT;
				byte[1] = 0;
				byte[2] = 0;
				byte[3] = 0;
				ISP_Swap((uint8_t*) &byte);
				sendHeader(4);
				UART_Tx_Checksum(CMD_READ_LOCK_ISP, 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(byte[receiveBuffer[1]-1], 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(0,1);
				break;

			case CMD_PROGRAM_LOCK_ISP:
				byte[0] = receiveBuffer[1];
				byte[1] = receiveBuffer[2];
				byte[2] = receiveBuffer[3];
				byte[3] = receiveBuffer[4];
				ISP_Swap((uint8_t*) &byte);
				sendHeader(3);
				UART_Tx_Checksum(CMD_PROGRAM_LOCK_ISP, 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(0,1);
				break;

			case CMD_READ_OSCCAL_ISP:
				byte[0] = READ_OSCCAL_BYTE;
				byte[1] = 0;
				byte[2] = 0;
				byte[3] = 0;
				ISP_Swap((uint8_t*) &byte);
				sendHeader(4);
				UART_Tx_Checksum(CMD_READ_OSCCAL_ISP, 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(byte[receiveBuffer[1]-1], 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(0,1);
				break;

			case CMD_LOAD_ADDRESS: 
				address = receiveBuffer[4];
				address |= receiveBuffer[3]<<8;
				address |= receiveBuffer[2]<<16;
				address |= receiveBuffer[1]<<24;
				sendHeader(2);
				UART_Tx_Checksum(CMD_LOAD_ADDRESS, 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(0,1);
				break;

			case CMD_READ_FLASH_ISP:
				len = receiveBuffer[1]<<8;
				len|= receiveBuffer[2];
				sendHeader(len+3);
				UART_Tx_Checksum(CMD_READ_FLASH_ISP, 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				for(i=0; i<len; i+=2){
					byte[0] = READ_FLASH_LOW_BYTE;
					byte[1] = (uint8_t)(address>>8);
					byte[2] = (uint8_t)(address>>0);
					byte[3] = 0;
					ISP_Swap((uint8_t*) &byte);
					UART_Tx_Checksum(byte[3], 0);

					
					byte[0] = READ_FLASH_HIGH_BYTE;
					byte[1] = (uint8_t)(address>>8);
					byte[2] = (uint8_t)(address>>0);
					byte[3] = 0;
					ISP_Swap((uint8_t*) &byte);
					UART_Tx_Checksum(byte[3], 0);
					
					address++;
				}
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(0,1);
				break;


			case CMD_CHIP_ERASE_ISP: 
				sendHeader(2);
				byte[0] = PERFORM_CHIP_ERASE_0;
				byte[1] = PERFORM_CHIP_ERASE_1;
				byte[2] = 0;
				byte[3] = 0;
				ISP_Swap((uint8_t*) &byte);
				
				if(receiveBuffer[2]){
					readyBusyPolling();
				}else{
					_delay_ms(receiveBuffer[1]);
				}

				address = 0;

				UART_Tx_Checksum(CMD_CHIP_ERASE_ISP, 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(0,1);
				break;


			case CMD_PROGRAM_FLASH_ISP: 
				len = receiveBuffer[1]<<8;
				len|= receiveBuffer[2];
				writeMem = getPin(0, receiveBuffer[3]) ? receiveBuffer[5] : receiveBuffer[6];
				i = 0;
				uint8_t count, top;
				
				
				while(i<len){
					if(len-i<64){
						top = len-i;
					}else{
						top = 64;
					}
					for(count=0; count<top; i+=2, count++,	address++){
						byte[0] = 0x40;
						byte[1] = (uint8_t)(address>>8);
						byte[2] = (uint8_t)(address>>0);
						byte[3] = receiveBuffer[i+10];
						ISP_Swap((uint8_t*) &byte);
						//_delay_ms(receiveBuffer[4]);

						byte[0] = 0x48;
						byte[1] = (uint8_t)(address>>8);
						byte[2] = (uint8_t)(address>>0);
						byte[3] = receiveBuffer[i+11];
						ISP_Swap((uint8_t*) &byte);
						//_delay_ms(receiveBuffer[4]);
					}
					uint16_t pageno = address-64;
					byte[0] = 0x4C;
					byte[1] = (uint8_t)(pageno>>8);
					byte[2] = (uint8_t)(pageno>>0);
					byte[3] = 0;
					ISP_Swap((uint8_t*) &byte);
					
					readyBusyPolling();
					//_delay_ms(receiveBuffer[4]);
				}
				

				sendHeader(2);
				UART_Tx_Checksum(CMD_PROGRAM_FLASH_ISP, 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(0,1);
				break;

			case CMD_READ_EEPROM_ISP:
				len = receiveBuffer[1]<<8;
				len|= receiveBuffer[2];
				sendHeader(len+3);
				UART_Tx_Checksum(CMD_READ_EEPROM_ISP, 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				for(i=0; i<len; i++){
					byte[0] = READ_EEPROM_BYTE;
					byte[1] = (uint8_t)(address>>8);
					byte[2] = (uint8_t)(address>>0);
					byte[3] = 0;
					ISP_Swap((uint8_t*) &byte);
					UART_Tx_Checksum(byte[3], 0);
					address++;
				}
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(0,1);
				break;

			case CMD_PROGRAM_EEPROM_ISP:
				len = receiveBuffer[1]<<8;
				len|= receiveBuffer[2];
				sendHeader(3);
				UART_Tx_Checksum(CMD_PROGRAM_EEPROM_ISP, 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				for(i=0; i<len; i++){
					byte[0] = WRITE_EEPROM_BYTE;
					byte[1] = (uint8_t)(address>>8);
					byte[2] = (uint8_t)(address>>0);
					byte[3] = 1;//receiveBuffer[2+i];
					ISP_Swap((uint8_t*) &byte);
					address++;
				}
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(0,1);
				break;


			case CMD_LEAVE_PROGMODE_ISP: 
				sendHeader(2);
				PORTB = reset ? clrPin(DD_RESET, PORTB) : setPin(DD_RESET, PORTB);
				UART_Tx_Checksum(CMD_LEAVE_PROGMODE_ISP, 0);
				UART_Tx_Checksum(STATUS_CMD_OK, 0);
				UART_Tx_Checksum(0,1);
				break;
			default:
				sendHeader(2);
				UART_Tx_Checksum(receiveBuffer[0], 0);
				UART_Tx_Checksum(STATUS_CMD_UNKNOWN, 0);
				UART_Tx_Checksum(0,1);
				

		}
		sequenceNumber++;

		
	}
	return 0;
}
void readyBusyPolling(void){
	uint8_t byte[4];
	do{
		byte[0] = 0xF0;
		byte[1] = 0;
		byte[2] = 0;
		byte[3] = 0;
		ISP_Swap((uint8_t*) &byte);
	}while(byte[3] == 1);
}
void sendHeader(uint16_t size){
	UART_Tx_Checksum(MESSAGE_START, 0);
	UART_Tx_Checksum(sequenceNumber, 0);
	UART_Tx_Checksum((uint8_t) (size>>8), 0);
	UART_Tx_Checksum((uint8_t) size, 0);
	UART_Tx_Checksum(TOKEN, 0);
}

uint8_t calcSckDur(uint16_t freq) { 
	uint8_t sck_dur;
    if (STK500){ 
      if (freq >= 1843200) 
        sck_dur = 0; 
      else if (freq >= 460800) 
        sck_dur = 1; 
      else if (freq >= 115200) 
        sck_dur = 2; 
      else if (freq >= 57600) 
        sck_dur = 3; 
      else 
        sck_dur = ceil(1/(2 * B * freq * T_STK500) - 10/B); 
    } else { // if (AVRISP) 
      if (freq >= 921600) 
        sck_dur = 0; 
      else if (freq >= 230400) 
        sck_dur = 1; 
      else if (freq >= 57600) 
        sck_dur = 2; 
      else if (freq >= 28800) 
        sck_dur = 3; 
      else 
        sck_dur = ceil(1/(2 * B * freq * T_AVRISP) - 10/B); 
    } 
 
    return fmin(254, sck_dur);  // 255 is an illegal value 
} 
