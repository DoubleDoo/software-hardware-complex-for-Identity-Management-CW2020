
#include "data.h"

uint16_t devAddr = (0x50 << 1);
uint16_t startaddressfordata=0x1000;

void initConstants()
{
	sconstants.blockscount=3;
}

void sendAllData()
{
	CDC_Transmit_FS("begin", 5);
	for(uint16_t i=0;i<sconstants.blockscount;i++)
	{
		char buf[64]="abc";
		readFromEeprom(startaddressfordata+64*i, buf,64);
		HAL_Delay(10);
		CDC_Transmit_FS(buf, 64);
		HAL_Delay(10);
	}
	HAL_Delay(10);
	CDC_Transmit_FS("end", 3);
}

void addDataBlock(uint8_t* data)
{
	sconstants.blockscount++;
	menu.pointer=sconstants.blockscount-1;
	accauntBlock buf [sconstants.blockscount+1];
	for(uint16_t i=0;i<sconstants.blockscount-1;i++)
	{
		buf[i]=menu.blocks[i];
	}
	writeToEeprom(startaddressfordata+64*(sconstants.blockscount-1), data,64);
	char buf2[64]="";
	readFromEeprom(startaddressfordata+64*(sconstants.blockscount-1), buf2,64);
	stringToStruct(&buf2, &buf[sconstants.blockscount-1]);
	menu.blocks=buf;
	updateScreen();
}

void initMenu()
{
	 menu.pointer=-1;
	 accauntBlock blocks [sconstants.blockscount+1];
	 for(uint16_t i=0;i<sconstants.blockscount;i++)
	 {
		 char buf[64]="";
		 readFromEeprom(startaddressfordata+64*i, buf,64);
		 stringToStruct(&buf, &blocks[i]);
	 }
	 menu.blocks=blocks;
	 updateScreen();
}

void updateScreen()
{
	if(menu.pointer<-1)
	{
		menu.pointer++;
	}
	else if(menu.pointer>sconstants.blockscount-1)
	{
		menu.pointer--;
	}
	else if(menu.pointer!=-1)
	{
		visualizeStruct(&menu.blocks[menu.pointer]);
	}
	else
	{
		ssd1306_Fill(Black);
		ssd1306_SetCursor(40,20);
		ssd1306_WriteString("settings", Font_7x10, White);
		ssd1306_UpdateScreen();
	}
}

void stringToStruct(char* inn, accauntBlock* out)
{
 memcpy( out->login, &inn[0],sizeof(out->login));
 memcpy( out->password, &inn[16], sizeof(out->password));
 memcpy( out->url, &inn[32], sizeof(out->url));
 memcpy( out->number, &inn[48], sizeof(out->number));
}

void structToString(accauntBlock* inn,char* out)
{
 	memcpy( &out[0],inn->login, sizeof(inn->login));
 	memcpy( &out[16],inn->password, sizeof(inn->password));
 	memcpy( &out[32],inn->url, sizeof(inn->url));
 	memcpy( &out[48],inn->number, sizeof(inn->number));
}

void visualizeStruct(accauntBlock* inn)
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(40,20);
	ssd1306_WriteString(inn->url, Font_7x10, White);
	ssd1306_SetCursor(40,30);
	ssd1306_WriteString(inn->login, Font_7x10, White);
	ssd1306_SetCursor(40,40);
	ssd1306_WriteString(inn->password, Font_7x10, White);
	ssd1306_UpdateScreen();
	//HAL_Delay(100);
}


void writeToEeprom(uint16_t memoryAddres, uint8_t* data,uint16_t dataLength)
{
	HAL_StatusTypeDef status;
	HAL_I2C_Mem_Write(&hi2c1, devAddr, memoryAddres, I2C_MEMADD_SIZE_16BIT, (uint8_t*)data, dataLength, HAL_MAX_DELAY);
	status = HAL_I2C_IsDeviceReady(&hi2c1, devAddr, 1,HAL_MAX_DELAY);
	while(status != HAL_OK)
	{
		status = HAL_I2C_IsDeviceReady(&hi2c1, devAddr, 1,HAL_MAX_DELAY);
	}
	//ssd1306_SetCursor(0,0);
	//ssd1306_WriteString(data, Font_7x10, White);
	// HAL_Delay(100);
}

void readFromEeprom(uint16_t memoryAddres, uint8_t* data,uint16_t dataLength)
{
	HAL_StatusTypeDef status;
	HAL_I2C_Mem_Read(&hi2c1, devAddr, memoryAddres, I2C_MEMADD_SIZE_16BIT,(uint8_t*)data, dataLength, HAL_MAX_DELAY);
	status = HAL_I2C_IsDeviceReady(&hi2c1, devAddr, 1,HAL_MAX_DELAY);
	while(status != HAL_OK)
	{
		status = HAL_I2C_IsDeviceReady(&hi2c1, devAddr, 1,HAL_MAX_DELAY);
	}
	//ssd1306_SetCursor(0,20);
	//ssd1306_WriteString(data, Font_7x10, White);
   // HAL_Delay(100);

}

