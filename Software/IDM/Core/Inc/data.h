
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
	uint16_t datacount;
	uint16_t blockscount;
	uint16_t startaddressfordata;
	uint16_t devisescount;
	uint16_t startaddressfordevices;
	uint16_t password;
} constants;




menuAB menu;
constants sconstants;
int16_t  pointer;
int16_t  updownpointer;
uint16_t  password[6];
uint16_t  imputpassword[6];







