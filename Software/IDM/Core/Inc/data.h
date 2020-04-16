
#include "main.h"
//#include "stm32f2xx_hal.h"

#define usbBlockSize 64


typedef struct {
	char*  login [16];
	char*  password [16];
	char* url[16];
	char* number[16];
} accauntBlock;

typedef struct {
	int16_t  pointer;
	accauntBlock* blocks;
} menuAB;

typedef struct {
	uint8_t datacount;
	uint8_t blockscount;
	uint8_t startaddressfordata;
	uint8_t devisescount;
	uint8_t startaddressfordevices;
	uint8_t password;
} constants;




menuAB menu;
constants sconstants;
int8_t  pointer;
int8_t  updownpointer;
uint8_t  password[6];
uint8_t  imputpassword[6];







