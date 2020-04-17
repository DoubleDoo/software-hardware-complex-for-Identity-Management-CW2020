#include "main.h"

#define usbBlockSize 64

void writeToEeprom(uint16_t memoryAddres, uint8_t *data, uint16_t dataLength);

void readFromEeprom(uint16_t memoryAddres, uint8_t *data, uint16_t dataLength);

