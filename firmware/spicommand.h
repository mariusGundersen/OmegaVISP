
// *****************[ ISP message constants ]***************************

#define PROGRAMMING_ENABLE_0					0xAC
#define PROGRAMMING_ENABLE_1					0x53
#define READ_DEVICE_CODE						0x30


// *****************[ FUSE access ]*************************************
#define READ_FUSE_EXTENDED_1					0x50
#define READ_FUSE_EXTENDED_2					0x00
#define READ_FUSE_HIGH_1						0x58
#define READ_FUSE_HIGH_2						0x08
#define READ_FUSE_LOW_1							0x50
#define READ_FUSE_LOW_2							0x08


// *****************[ FLASH memory access ]*****************************
#define READ_FLASH_HIGH_BYTE					0x28
#define READ_FLASH_LOW_BYTE						0x20
#define WRITE_FLASH_HIGH_BYTE					0x68
#define WRITE_FLASH_LOW_BYTE					0x60


// *****************[ EEPROM memory access ]****************************
#define READ_EEPROM_BYTE						0xA0
#define WRITE_EEPROM_BYTE						0xC0



// *****************[ CALIBRATION byte access ]*************************
#define READ_OSCCAL_BYTE						0x38
#define WRITE_OSCCAL_BYTE						0xAC


// *****************[ LOCK bits access ]********************************
#define READ_LOCK_BIT							0x58
#define WRITE_LOCK_BIT							0xAC


// *****************[ CHIP erase ]**************************************
#define PERFORM_CHIP_ERASE_0					0xAC
#define PERFORM_CHIP_ERASE_1					0x80
