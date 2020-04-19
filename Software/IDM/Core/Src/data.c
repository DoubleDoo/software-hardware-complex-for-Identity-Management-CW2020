#include "data.h"

devAddr = (0x50 << 1);
startaddressfordata = 0x1000;

void deviceIsntInit() {
	if (M5PCIDdefaultIsGetted) {
		if (isInit == 0) {
			initStatus = 1;
			initChoseProcess();
		} else if (ProtectType == 2) {
			ssd1306_Fill(Black);
			ssd1306_SetCursor(2, 2);
			ssd1306_WriteString("Conect device to", Font_7x10, White);
			ssd1306_SetCursor(2, 12);
			ssd1306_WriteString("your safe PC", Font_7x10, White);
			ssd1306_UpdateScreen();
		} else if (ProtectType == 3) {
			ssd1306_Fill(Black);
			ssd1306_SetCursor(2, 2);
			ssd1306_WriteString("Conect device to", Font_7x10, White);
			ssd1306_SetCursor(2, 12);
			ssd1306_WriteString("your safe PC", Font_7x10, White);
			ssd1306_UpdateScreen();
		}

	} else {
		ssd1306_Fill(Black);
		ssd1306_SetCursor(2, 2);
		ssd1306_WriteString("Start init from", Font_7x10, White);
		ssd1306_SetCursor(2, 12);
		ssd1306_WriteString("your safe PC", Font_7x10, White);
		ssd1306_UpdateScreen();
	}

}

void uploadIsInit() {
	writeToEeprom(0x0000, &isInit, 1);
}

void downloadIsInit() {
	readFromEeprom(0x0000, &isInit, 1);
//	ssd1306_SetCursor(2, 2);
//	ssd1306_WriteStringUint(isInit, Font_7x10, White);
//	ssd1306_UpdateScreen();
}

void uploadSecureOpt() {
	writeToEeprom(0x0000 + 1, &ProtectType, 1);
}

void downloadSecureOpt() {
	readFromEeprom(0x0000 + 1, &ProtectType, 1);
//	ssd1306_SetCursor(12, 2);
//	ssd1306_WriteStringUint(ProtectType, Font_7x10, White);
//	ssd1306_UpdateScreen();
}

void uploadPassword() {
	writeToEeprom(0x0000 + 2, &password, 6);
}

void downloadPassword() {
	readFromEeprom(0x0000 + 2, &password, 6);
//	ssd1306_SetCursor(12, 50);
//	ssd1306_WriteStringUint(password[0], Font_7x10, White);
	//ssd1306_WriteStringUint(password[1], Font_7x10, White);
	//ssd1306_WriteStringUint(password[2], Font_7x10, White);
	//ssd1306_WriteStringUint(password[3], Font_7x10, White);
	//ssd1306_WriteStringUint(password[4], Font_7x10, White);
	//ssd1306_UpdateScreen();
}

void uploadPCIDcount() {
	writeToEeprom(0x0200, &M5PPCIDCount, 2);
}

void downloadPCIDcount() {
	readFromEeprom(0x0200, &M5PPCIDCount, 2);
	//ssd1306_SetCursor(22, 2);
//	ssd1306_WriteStringUint(M5PPCIDCount, Font_7x10, White);
	//ssd1306_UpdateScreen();
}

void uploadDataCount() {
	writeToEeprom(0x0000 + 9, &DataCount, 1);
}

void downloadDataCount() {
	readFromEeprom(0x0000 + 9, &DataCount, 1);
	//ssd1306_SetCursor(32, 2);
	//ssd1306_WriteStringUint(DataCount, Font_7x10, White);
	//ssd1306_UpdateScreen();
}
void uploadIsfirstPC() {
	writeToEeprom(0x0000 + 10, &M5PCIDdefaultIsGetted, 1);
}

void downloadIsfirstPCt() {
	readFromEeprom(0x0000 + 10, &M5PCIDdefaultIsGetted, 1);
//	ssd1306_SetCursor(2, 2);
//	ssd1306_WriteStringUint(isInit, Font_7x10, White);
//	ssd1306_UpdateScreen();
}

//addDeviceEnable

void uploadaddDeviceEnable() {
	writeToEeprom(0x0000 + 11, &addDeviceEnable, 1);
}

void downloadaddDeviceEnable() {
	readFromEeprom(0x0000 + 11, &addDeviceEnable, 1);
}

void uploadPrivate() {
	writeToEeprom(0x0000 + 12, &privateKey, 20);
}

void downloadPrivate() {
	readFromEeprom(0x0000 + 12, &privateKey, 20);
}

void uploadadPublic() {
	writeToEeprom(0x0000 + 32, &publicKey, 20);
}

void downloadPublic() {
	readFromEeprom(0x0000 + 32, &publicKey, 20);
}

void uploadPCIDmas() {

	writeToEeprom(0x0300 + 100, &PCIDFour, 24);
	writeToEeprom(0x0300 + 150, &PCIDFive, 24);
	writeToEeprom(0x0300 + 200, &PCIDOne, 24);

	writeToEeprom(0x0300 + 400, &PCIDSeven, 24);
	writeToEeprom(0x0300 + 450, &PCIDSix, 24);

	//writeToEeprom(0x0000,&isInit ,1);
}

void downloadPCIDmas() {

//	for(uint8_t i=0;i<M5PPCIDCount;i++)
//	{
	//readFromEeprom(0x0300,&PCIDOne ,24);
	//readFromEeprom(0x0300+24,&PCIDSeven ,24);
	//readFromEeprom(0x0300+48,&PCIDSix ,24);
	//readFromEeprom(0x0300+72,&PCIDFour ,24);
	//readFromEeprom(0x0300+96,&PCIDFive ,24);
//
	//readFromEeprom(0x0300+260,&PCIDSeven ,24);
	//readFromEeprom(0x0300+310,&PCIDSix ,24);
	readFromEeprom(0x0300 + 100, &PCIDFour, 24);
	readFromEeprom(0x0300 + 150, &PCIDFive, 24);
	readFromEeprom(0x0300 + 200, &PCIDOne, 24);

	readFromEeprom(0x0300 + 400, &PCIDSeven, 24);
	readFromEeprom(0x0300 + 450, &PCIDSix, 24);
	//}

}

uint8_t lt[] = {

0B00000000, 0B00000000, 0B00000001, 0B00000011, 0B00000111, 0B00001111,
		0B00011111, 0B00111111, 0B00111111, 0B00011111, 0B00001111, 0B00000111,
		0B00000011, 0B00000001, 0B00000000, 0B00000000 };

uint8_t rt[] = {

0B00000000, 0B00000000, 0B10000000, 0B11000000, 0B11100000, 0B11110000,
		0B11111000, 0B11111100, 0B11111100, 0B11111000, 0B11110000, 0B11100000,
		0B11000000, 0B10000000, 0B00000000, 0B00000000 };

uint8_t cancel[] = {

0B10000001, 0B01000010, 0B00100100, 0B00011000, 0B00011000, 0B00100100,
		0B01000010, 0B10000001 };

uint8_t ok[] = {

0B00000000, 0B00000001, 0B00000010, 0B00000100, 0B10001000, 0B01010000,
		0B00100000, 0B00000000 };

uint8_t line[] = {

0B00000000, 0B11111111, 0B00000000, 0B00000000, 0B00000000, 0B00000000,
		0B00000000, 0B00000000 };

uint8_t linebold[] = {

0B00000000, 0B11111111, 0B11111111, 0B00000000, 0B00000000, 0B00000000,
		0B00000000, 0B00000000 };

uint8_t upwd[] = {

0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000,
		0B00000001, 0B10000000, 0B00000011, 0B11000000, 0B00000111, 0B11100000,
		0B00001111, 0B11110000, 0B00011111, 0B11111000

};

uint8_t downwd[] = { 0B00011111, 0B11111000, 0B00001111, 0B11110000, 0B00000111,
		0B11100000, 0B00000011, 0B11000000, 0B00000001, 0B10000000, 0B00000000,
		0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000

};

uint8_t newDev[] = {

0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000,
		0B00000000, 0B00000000, 0B00001111, 0B10000000, 0B00000001, 0B11110000,
		0B01111111, 0B11111111, 0B11111111, 0B11111110, 0B01000000, 0B00000000,
		0B00000000, 0B00000010, 0B01000000, 0B00000000, 0B00000000, 0B00000010,
		0B01000000, 0B00000001, 0B10000000, 0B00000010, 0B01000000, 0B00000001,
		0B10000000, 0B00000010, 0B01000000, 0B00000111, 0B11100000, 0B00000010,
		0B01000000, 0B00000111, 0B11100000, 0B00000010, 0B01000000, 0B00000001,
		0B10000000, 0B00000010, 0B01000000, 0B00000001, 0B10000000, 0B00000010,
		0B01000000, 0B00000000, 0B00000000, 0B00000010, 0B01000000, 0B00000000,
		0B00000000, 0B00000010, 0B01111111, 0B11111111, 0B11111111, 0B11111110,
		0B00000000, 0B00000000, 0B00000000, 0B00000000 };

uint8_t restoreDev[] = {

0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000,
		0B00000000, 0B00000000, 0B00001111, 0B10000000, 0B00000001, 0B11110000,
		0B01111111, 0B11111111, 0B11111111, 0B11111110, 0B01000000, 0B00000001,
		0B00000000, 0B00000010, 0B01000000, 0B00000011, 0B00000000, 0B00000010,
		0B01000000, 0B00000111, 0B10000000, 0B00000010, 0B01000000, 0B00000011,
		0B01000000, 0B00000010, 0B01000000, 0B00000001, 0B00100000, 0B00000010,
		0B01000000, 0B00001000, 0B00100000, 0B00000010, 0B01000000, 0B00000100,
		0B01000000, 0B00000010, 0B01000000, 0B00000011, 0B10000000, 0B00000010,
		0B01000000, 0B00000000, 0B00000000, 0B00000010, 0B01000000, 0B00000000,
		0B00000000, 0B00000010, 0B01111111, 0B11111111, 0B11111111, 0B11111110,
		0B00000000, 0B00000000, 0B00000000, 0B00000000 };

uint8_t gear[] = { 0B00000000, 0B00000001, 0B10000000, 0B00000000, 0B00000000,
		0B00000011, 0B11000000, 0B00000000, 0B00000000, 0B00000111, 0B11100000,
		0B00000000, 0B00011110, 0B00001111, 0B11110000, 0B01111000, 0B00011111,
		0B10011110, 0B01111001, 0B11111000, 0B00011111, 0B11111100, 0B00111111,
		0B11111000, 0B00011111, 0B11100000, 0B00000111, 0B11111000, 0B00001111,
		0B00000000, 0B00000000, 0B11111000, 0B00001110, 0B00000111, 0B11100000,
		0B01110000, 0B00000110, 0B00001110, 0B01110000, 0B01100000, 0B00000110,
		0B00011000, 0B00011000, 0B01100000, 0B00001100, 0B00110000, 0B00001100,
		0B00110000, 0B00011100, 0B01100001, 0B10000110, 0B00111000, 0B00111100,
		0B11000011, 0B11000011, 0B00111100, 0B01111001, 0B10000111, 0B11100001,
		0B10011110, 0B11110001, 0B10001110, 0B01110001, 0B10011111, 0B11110001,
		0B10001110, 0B01110001, 0B10011111, 0B01111001, 0B10000111, 0B11100001,
		0B10011110, 0B00111100, 0B11000011, 0B11000011, 0B00111100, 0B00011100,
		0B01100001, 0B10000110, 0B00111000, 0B00001100, 0B00110000, 0B00001100,
		0B00110000, 0B00000110, 0B00011000, 0B00011000, 0B01100000, 0B00000110,
		0B00001110, 0B01110000, 0B01100000, 0B00001110, 0B00000111, 0B11100000,
		0B01110000, 0B00001111, 0B00000000, 0B00000000, 0B11111000, 0B00011111,
		0B11100000, 0B00000111, 0B11111000, 0B00011111, 0B11111100, 0B00111111,
		0B11111000, 0B00011111, 0B10011110, 0B01111001, 0B11111000, 0B00011110,
		0B00001111, 0B11110000, 0B01111000, 0B00000000, 0B00000111, 0B11100000,
		0B00000000, 0B00000000, 0B00000011, 0B11000000, 0B00000000, 0B00000000,
		0B00000001, 0B10000000, 0B00000000

};
/*
 oled.OLED_Write_To_Bufer(x,y,w,h,zero);
 else if (data==0x31)
 oled.OLED_Write_To_Bufer(x,y,w,h,one);
 else if (data==0x32)
 oled.OLED_Write_To_Bufer(x,y,w,h,two);
 else if (data==0x33)
 oled.OLED_Write_To_Bufer(x,y,w,h,three);
 else if (data==0x34)
 oled.OLED_Write_To_Bufer(x,y,w,h,four);
 else if (data==0x35)
 oled.OLED_Write_To_Bufer(x,y,w,h,five);
 else if (data==0x36)
 oled.OLED_Write_To_Bufer(x,y,w,h,six);
 else if (data==0x37)
 oled.OLED_Write_To_Bufer(x,y,w,h,seven);
 else if (data==0x38)
 oled.OLED_Write_To_Bufer(x,y,w,h,eight);
 else if (data==0x39)
 oled.OLED_Write_To_Bufer(x,y,w,h,nine);

 */

void initConstants() {
	dataTransferEnable = 0;
	isInit = 0;
	ProtectType = 0;
	settingsMenuStatus = 0;
	dataControlMenuStatus = 0;
	DataCount = 0;
	initStatus = 0;
	initStatusStep1 = 0;
	initStatusStep2 = 0;
	restoreStatusStep1 = 0;
	restoreStatusStep2 = 0;
	menuStatus = 0;
	restoreStatus = 0;
	setPasswordStatus = 0;
	settingsStatus = 0;
	datasettingsStatus = 0;
	setPasswordStep1 = 0;
	setPasswordStep2 = 0;

	setProtectTypeStep1 = 0;
	setProtectTypeStep2 = 0;
	passwordInputStatus = 0;

	leftButtonStatus = 0;
	rightButtonStatus = 0;
	bothButtonStatus = 0;

	M5PCIDdefaultIsGetted = 0;

	downloadIsInit();
	downloadSecureOpt();
	downloadPassword();
	downloadPCIDcount();
	downloadDataCount();
	//DataCount = DataCount;
	downloadaddDeviceEnable();
	downloadPCIDcount();
	downloadIsfirstPCt();
	downloadPublic();
	downloadPrivate();
	downloadPCIDmas();
	//generatePassFrase();

}

void initChoseProcess() {
	generatePassFrase();
	ssd1306_Fill(Black);
	ssd1306_Write_To_Bufer(16, 24, 32, 16, newDev);
	ssd1306_Write_To_Bufer(80, 24, 32, 16, restoreDev);
	ssd1306_UpdateScreen();
}

void initProcess1() {
	initStatus = 0;
	initStatusStep1 = 1;
	pointer = -1;
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, 5);
	ssd1306_WriteString("Write all 12 words in a safe place", Font_7x10, White);
	ssd1306_SetCursor(2, 15);
	ssd1306_WriteString("into a safe place.", Font_7x10, White);
	ssd1306_SetCursor(2, 25);
	ssd1306_WriteString("Press two buttons if you spelled the word", Font_7x10,
			White);
	ssd1306_SetCursor(2, 35);
	ssd1306_WriteString("if you wrote word", Font_7x10, White);
	ssd1306_SetCursor(2, 45);
	ssd1306_WriteString("or to continue.", Font_7x10, White);
	ssd1306_UpdateScreen();
	//
	//char* passFrase[12];

}

void initProcess1Next() {
	//Font_16x26  Font_11x18
	pointer++;
	if (pointer < 12) {

		ssd1306_Fill(Black);
		ssd1306_SetCursor(40, 10);
		char *text = "Word ";
		//strcat(text, (char)(pointer+1));
		ssd1306_WriteString(text, Font_7x10, White);
		ssd1306_WriteStringUint((pointer + 1), Font_7x10, White);
		ssd1306_SetCursor(25, 25);
		ssd1306_WriteString(passFrase[pointer], Font_16x26, White);
		ssd1306_UpdateScreen();
		//char* passFrase[12];
	} else {
		//fCheckStatus=1;
		//initStatus=0;
		initStatusStep1 = 0;
		initStatusStep2 = 1;
		initProcess2();
	}

}

void initProcess2() {

	pointer = -1;
	ssd1306_Fill(Black);
	ssd1306_SetCursor(15, 10);
	ssd1306_WriteString("Check 4 random", Font_7x10, White);
	ssd1306_SetCursor(45, 20);
	ssd1306_WriteString("words..", Font_7x10, White);
	ssd1306_Write_To_Bufer(2, 54, 8, 8, cancel);
	ssd1306_Write_To_Bufer(120, 54, 8, 8, ok);
	ssd1306_UpdateScreen();
	generateRandomNumbers(12, 0xf);

}

void initProcess2Next() {

	pointer++;
	if (pointer < 4) {
		//uint16_t num;
		//num=HAL_RNG_GetRandomNumber(&hrng)&0x0000000F;
		ssd1306_Fill(Black);
		ssd1306_SetCursor(40, 10);
		char *text = "Word ";
		//strcat(text, (char)(pointer+1));
		ssd1306_WriteString(text, Font_7x10, White);
		ssd1306_WriteStringUint(RNGNumbers[pointer] + 1, Font_7x10, White);
		ssd1306_SetCursor(25, 25);
		ssd1306_WriteString(passFrase[RNGNumbers[pointer]], Font_16x26, White);
		ssd1306_Write_To_Bufer(2, 54, 8, 8, cancel);
		ssd1306_Write_To_Bufer(120, 54, 8, 8, ok);
		ssd1306_UpdateScreen();
	} else {
		//fCheckStatus=1;
		//initStatus=0;
		initStatusStep2 = 0;
		setPasswordProcess1();
	}

}

void generateExtraData() {
	isInit = 1;
	uploadIsInit();
	uploadSecureOpt();
	uploadPassword();
	uploadPCIDcount();
	DataCount = 0;
	//DataCount = DataCount;
	uploadDataCount();

	//uploadPCIDmas();

	downloadIsInit();
	downloadSecureOpt();
	downloadPassword();
	downloadPCIDcount();
	downloadDataCount();

	//downloadPCIDmas();
	//HAL_Delay(10000);
}

void clearDevice() {
	isInit = 0;
	ProtectType = 0;
	settingsMenuStatus = 0;
	dataControlMenuStatus = 0;
	DataCount = 0;
	initStatus = 0;
	initStatusStep1 = 0;
	initStatusStep2 = 0;
	restoreStatusStep1 = 0;
	restoreStatusStep2 = 0;
	menuStatus = 0;
	restoreStatus = 0;
	setPasswordStatus = 0;
	settingsStatus = 0;
	datasettingsStatus = 0;
	setPasswordStep1 = 0;
	setPasswordStep2 = 0;
	setProtectTypeStep1 = 0;
	setProtectTypeStep2 = 0;
	passwordInputStatus = 0;
	leftButtonStatus = 0;
	rightButtonStatus = 0;
	bothButtonStatus = 0;
	M5PCIDdefaultIsGetted = 0;
	uploadIsInit();
	uploadSecureOpt();
	uploadPassword();
	uploadPCIDcount();
	uploadDataCount();
	//uploadPCIDmas();

	uint8_t nul = 0;
	for (int i = 0; i < 1000; i++) {
		writeToEeprom(i, &nul, 1);
	}
	for (int i = 0; i < 1000; i++) {
		writeToEeprom(0x0300 + i, &nul, 1);
	}
	for (int i = 0; i < 1000; i++) {
		writeToEeprom(0x1000 + i, &nul, 1);
	}

}

void restoreProcess1() {
	initStatus = 0;
	restoreStatusStep1 = 1;
	pointer = -1;

	ssd1306_Fill(Black);
	ssd1306_SetCursor(10, 10);
	ssd1306_WriteString("Restore mode,", Font_7x10, White);
	ssd1306_SetCursor(10, 20);
	ssd1306_WriteString("init your device", Font_7x10, White);
	ssd1306_SetCursor(10, 30);
	ssd1306_WriteString("by using PC app", Font_7x10, White);
	ssd1306_SetCursor(10, 50);
	ssd1306_WriteString("Press any key", Font_7x10, White);
	ssd1306_UpdateScreen();

}

void setPasswordProcess1() {
	pointer = 0;
	updownpointer = 0;
	setPasswordStep1 = 1;
	ssd1306_Fill(Black);
	ssd1306_SetCursor(7, 10);
	ssd1306_WriteString("Create password", Font_7x10, White);
	ssd1306_SetCursor(27, 20);
	ssd1306_WriteString("for device", Font_7x10, White);
	ssd1306_Write_To_Bufer(28, 50, 8, 8, line);
	ssd1306_Write_To_Bufer(44, 50, 8, 8, line);
	ssd1306_Write_To_Bufer(60, 50, 8, 8, line);
	ssd1306_Write_To_Bufer(76, 50, 8, 8, line);
	ssd1306_Write_To_Bufer(92, 50, 8, 8, line);
	ssd1306_SetCursor(28 + pointer * 16, 40);
	ssd1306_WriteStringUint(updownpointer, Font_7x10, White);
	ssd1306_Write_To_Bufer(28, 50, 8, 8, linebold);
	ssd1306_UpdateScreen();

}

void setPasswordProcess1Next() {
	password[pointer] = updownpointer;
	if (pointer < 4) {
		ssd1306_Write_To_Bufer(28, 50, 8, 8, line);
		ssd1306_Write_To_Bufer(44, 50, 8, 8, line);
		ssd1306_Write_To_Bufer(60, 50, 8, 8, line);
		ssd1306_Write_To_Bufer(76, 50, 8, 8, line);
		ssd1306_Write_To_Bufer(92, 50, 8, 8, line);
		pointer++;
		ssd1306_SetCursor(28 + pointer * 16, 40);
		ssd1306_WriteStringUint(updownpointer, Font_7x10, White);
		ssd1306_Write_To_Bufer(28 + pointer * 16, 50, 8, 8, linebold);
		ssd1306_UpdateScreen();
		//uint16_t num;
		//num=HAL_RNG_GetRandomNumber(&hrng)&0x0000000F;
		//ssd1306_Fill(Black);
		//setPasswordProcess1();
		//ssd1306_SetCursor(28+pointer*16,40);
		//char* text="Word ";
		//strcat(text, (char)(pointer+1));
		//ssd1306_WriteString(text, Font_7x10, White);

		//ssd1306_UpdateScreen();
		//char* passFrase[12];
	} else {
		//fCheckStatus=1;
		//initStatus=0;
		//generateandcheckPassword();
		setPasswordStep2 = 1;
		setPasswordStep1 = 0;
		setPasswordProcess2();
	}

}

void setPasswordProcess1Up() {
	updownpointer++;
	if (updownpointer > 9) {
		updownpointer = 0;
	}

	ssd1306_SetCursor(28 + (pointer) * 16, 40);
	ssd1306_WriteStringUint(updownpointer, Font_7x10, White);
	ssd1306_UpdateScreen();
}

void setPasswordProcess1Down() {
	updownpointer--;
	if (updownpointer < 0) {
		updownpointer = 9;
	}
	ssd1306_SetCursor(28 + (pointer) * 16, 40);
	ssd1306_WriteStringUint(updownpointer, Font_7x10, White);
	ssd1306_UpdateScreen();
}

void setPasswordProcess2() {
	pointer = 0;
	updownpointer = 0;
	setPasswordStep2 = 1;
	ssd1306_Fill(Black);
	ssd1306_SetCursor(20, 10);
	ssd1306_WriteString("Write password", Font_7x10, White);
	//ssd1306_SetCursor(50, 20);
	//ssd1306_WriteString("again", Font_7x10, White);
	ssd1306_Write_To_Bufer(28, 50, 8, 8, line);
	ssd1306_Write_To_Bufer(44, 50, 8, 8, line);
	ssd1306_Write_To_Bufer(60, 50, 8, 8, line);
	ssd1306_Write_To_Bufer(76, 50, 8, 8, line);
	ssd1306_Write_To_Bufer(92, 50, 8, 8, line);
	ssd1306_SetCursor(28 + pointer * 16, 40);
	ssd1306_WriteStringUint(updownpointer, Font_7x10, White);
	ssd1306_Write_To_Bufer(28 + pointer * 16, 50, 8, 8, linebold);
	ssd1306_UpdateScreen();

}

void setPasswordProcess2Next() {
	imputpassword[pointer] = updownpointer;
	if (pointer < 4) {

		ssd1306_Write_To_Bufer(28, 50, 8, 8, line);
		ssd1306_Write_To_Bufer(44, 50, 8, 8, line);
		ssd1306_Write_To_Bufer(60, 50, 8, 8, line);
		ssd1306_Write_To_Bufer(76, 50, 8, 8, line);
		ssd1306_Write_To_Bufer(92, 50, 8, 8, line);

		pointer++;
		ssd1306_SetCursor(28 + pointer * 16, 40);
		ssd1306_WriteStringUint(updownpointer, Font_7x10, White);
		ssd1306_Write_To_Bufer(28 + pointer * 16, 50, 8, 8, linebold);

		ssd1306_UpdateScreen();
		//uint16_t num;
		//num=HAL_RNG_GetRandomNumber(&hrng)&0x0000000F;
		//ssd1306_Fill(Black);
		//setPasswordProcess1();
		//ssd1306_SetCursor(28+pointer*16,40);
		//char* text="Word ";
		//strcat(text, (char)(pointer+1));
		//ssd1306_WriteString(text, Font_7x10, White);

		//ssd1306_UpdateScreen();
		//char* passFrase[12];
	} else {
		/*
		 ssd1306_SetCursor(2,50);
		 ssd1306_WriteStringUint(password[0], Font_7x10, White);
		 ssd1306_WriteStringUint(password[1], Font_7x10, White);
		 ssd1306_WriteStringUint(password[2], Font_7x10, White);
		 ssd1306_WriteStringUint(password[3], Font_7x10, White);
		 ssd1306_WriteStringUint(password[4], Font_7x10, White);
		 ssd1306_WriteStringUint(imputpassword[0], Font_7x10, White);
		 ssd1306_WriteStringUint(imputpassword[1], Font_7x10, White);
		 ssd1306_WriteStringUint(imputpassword[2], Font_7x10, White);
		 ssd1306_WriteStringUint(imputpassword[3], Font_7x10, White);
		 ssd1306_WriteStringUint(imputpassword[4], Font_7x10, White);
		 ssd1306_UpdateScreen();*/
		if (passwordInputStatus == 0) {
			if (imputpassword[0] == password[0]
					&& imputpassword[1] == password[1]
					&& imputpassword[2] == password[2]
					&& imputpassword[3] == password[3]
					&& imputpassword[4] == password[4]) {

				setPasswordStep2 = 0;
				setProtectTypeProcess1();

			} else {
				setPasswordStep1 = 1;
				setPasswordStep2 = 0;
				password[0] = 0;
				password[1] = 0;
				password[2] = 0;
				password[3] = 0;
				password[4] = 0;
				imputpassword[0] = 0;
				imputpassword[1] = 0;
				imputpassword[2] = 0;
				imputpassword[3] = 0;
				imputpassword[4] = 0;
				setPasswordProcess1();
			}
		} else if (chpassComand == 1) {

			if (imputpassword[0] == password[0]
					&& imputpassword[1] == password[1]
					&& imputpassword[2] == password[2]
					&& imputpassword[3] == password[3]
					&& imputpassword[4] == password[4]) {
				uploadPassword();
				setPasswordStep2 = 0;
				settingsMenuStatus = 1;
				chpassComand = 0;
				settingsMenu();
			} else {
				setPasswordStep2 = 0;
				setPasswordProcess1();
			}
		} else {
			if (imputpassword[0] == password[0]
					&& imputpassword[1] == password[1]
					&& imputpassword[2] == password[2]
					&& imputpassword[3] == password[3]
					&& imputpassword[4] == password[4]) {
				setPasswordStep2 = 0;
				Unlocked = 1;
				menuStatus = 1;
				initMenu();
			} else {
				setPasswordProcess2();
			}
		}
	}
}

void setProtectTypeProcess1() {
	setProtectTypeStep1 = 1;
	pointer = ProtectType;
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, 10);
	ssd1306_WriteString("Choose secure mode", Font_7x10, White);
	ssd1306_Write_To_Bufer(2, 50, 8, 16, lt);
	ssd1306_Write_To_Bufer(120, 50, 8, 16, rt);
	setProtectTypeProcessDefault();
}

void setProtectTypeProcess1Next() {
	if (cProtectComand == 1) {
		ProtectType = pointer;
		uploadSecureOpt();
		setProtectTypeStep1 = 0;
		settingsMenuStatus = 1;
		cProtectComand = 0;
		settingsMenu();
	} else {
		ProtectType = pointer;
		generateExtraData();
		menuStatus = 1;
		Unlocked = 1;
		setProtectTypeStep1 = 0;
		initMenu();
	}

}

void setProtectTypeProcessDefault() {
	switch (pointer) {
	case 0:
		ssd1306_SetCursor(10, 35);
		ssd1306_WriteString("      none      ", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;
	case 1:
		ssd1306_SetCursor(10, 35);
		ssd1306_WriteString("    password    ", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;
	case 2:
		ssd1306_SetCursor(10, 35);
		ssd1306_WriteString("      PC ID     ", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;
	case 3:
		ssd1306_SetCursor(10, 35);
		ssd1306_WriteString("PC ID + password", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	}
}

void setProtectTypeProcess1Up() {
	pointer++;
	if (pointer > 3) {
		pointer = 0;

	}
	setProtectTypeProcessDefault();
}
void setProtectTypeProcess1Down() {
	pointer--;
	if (pointer < 0) {
		pointer = 3;
	}
	setProtectTypeProcessDefault();
}

void sendAllData() {
	CDC_Transmit_FS("begin(", 6);
	for (uint16_t i = 0; i < DataCount; i++) {
		char buf[16] = "abc";
		readFromEeprom(startaddressfordata + 64 * i, buf, 16);
		HAL_Delay(10);
		CDC_Transmit_FS(buf, 16);
		HAL_Delay(10);
		readFromEeprom(startaddressfordata + 64 * i + 32, buf, 32);
		HAL_Delay(10);
		CDC_Transmit_FS(buf, 32);
		HAL_Delay(10);
	}
	HAL_Delay(10);
	CDC_Transmit_FS(")end", 4);
}

void addDataBlock(uint8_t *data) {
	DataCount++;
	menu.pointer = DataCount - 1;
	accauntBlock buf[DataCount + 1];
	for (uint16_t i = 0; i < DataCount - 1; i++) {
		buf[i] = menu.blocks[i];
	}
	writeToEeprom(startaddressfordata + 64 * (DataCount - 1), data, 64);
	char buf2[64] = "";
	readFromEeprom(startaddressfordata + 64 * (DataCount - 1), buf2, 64);
	stringToStruct(&buf2, &buf[DataCount - 1]);
	menu.blocks = buf;
	updateScreen();
}

void initMenu() {
	menu.pointer = -1;
	accauntBlock blocks[DataCount + 1];
	for (uint16_t i = 0; i < DataCount; i++) {
		char buf[64] = "";
		readFromEeprom(startaddressfordata + 64 * i, buf, 64);
		stringToStruct(&buf, &blocks[i]);
	}
	menu.blocks = blocks;
	updateScreen();
}
//settingsMenu;menu.pointer
void updateScreen() {
	if (menu.pointer < -1) {
		menu.pointer++;
	} else if (menu.pointer > DataCount - 1) {
		menu.pointer--;
	} else if (menu.pointer != -1) {
		visualizeStruct(&menu.blocks[menu.pointer]);
	} else {
		ssd1306_Fill(Black);
		ssd1306_SetCursor(40, 20);
		ssd1306_Write_To_Bufer(48, 20, 32, 32, gear);

	}
	if (DataCount != 0) {
		if (menu.pointer > -1)
			ssd1306_Write_To_Bufer(2, 50, 8, 16, lt);
		if (menu.pointer < DataCount - 1)
			ssd1306_Write_To_Bufer(120, 50, 8, 16, rt);
	}

	ssd1306_UpdateScreen();
}

void chooseMainMenu() {
	if (menu.pointer == -1) {
		menuStatus = 0;
		settingsMenu();
	} else {
		menuStatus = 0;
		dataControlMenu(&menu.blocks[menu.pointer]);
	}
}

void settingsMenuDefault() {
	switch (pointer) {
	case 0:
		ssd1306_SetCursor(7, 30);
		ssd1306_WriteString(" Change password ", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;
	case 1:
		ssd1306_SetCursor(7, 30);
		ssd1306_WriteString("   Reset device  ", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;
	case 2:
		ssd1306_SetCursor(7, 30);
		ssd1306_WriteString("   Export mode   ", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;
	case 3:
		ssd1306_SetCursor(7, 30);
		ssd1306_WriteString("Change Protection", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;
	case 4:
		ssd1306_SetCursor(7, 30);
		ssd1306_WriteString("      Back       ", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	}
}

void settingsMenu() {
	settingsMenuStatus = 1;
	pointer = 0;
	ssd1306_Fill(Black);
	ssd1306_SetCursor(35, 5);
	ssd1306_WriteString("Settings", Font_7x10, White);
	ssd1306_Write_To_Bufer(2, 50, 8, 16, lt);
	ssd1306_Write_To_Bufer(120, 50, 8, 16, rt);
	settingsMenuDefault();
}

void settingsMenuUp() {
	pointer++;
	if (pointer > 4) {
		pointer = 0;

	}
	settingsMenuDefault();

}

void settingsMenuDown() {
	pointer--;
	if (pointer < 0) {
		pointer = 4;

	}
	settingsMenuDefault();

}

void settingsMenuSelect() {
	switch (pointer) {
	case 0:
		passwordChangeMenu();
		break;
	case 1:
		resetDeviceMenu();
		break;
	case 2:
		exportModeMenu();
		break;
	case 3:
		changeProtectionMenu();
		break;
	case 4:
		settingsMenuStatus = 0;
		menuStatus = 1;
		updateScreen();
		break;

	}

}

void resetDeviceMenu() {
	settingsMenuStatus = 0;
	ResetComand = 1;
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, 0);
	ssd1306_WriteString("Are you shure to ", Font_7x10, White);
	ssd1306_SetCursor(2, 10);
	ssd1306_WriteString("reset device?", Font_7x10, White);
	ssd1306_Write_To_Bufer(2, 54, 8, 8, cancel);
	ssd1306_Write_To_Bufer(120, 54, 8, 8, ok);
	ssd1306_UpdateScreen();

}

void changeProtectionMenu() {
	setProtectTypeStep1 = 1;
	cProtectComand = 1;
	ssd1306_Fill(Black);
	setProtectTypeProcess1();
	ssd1306_UpdateScreen();

}

void passwordChangeMenu() {
	passwordInputStatus = 1;
	settingsMenuStatus = 0;
	setPasswordStep1 = 1;
	chpassComand = 1;
	ssd1306_Fill(Black);
	setPasswordProcess1();
	ssd1306_UpdateScreen();

}

void exportModeMenu() {
	settingsMenuStatus = 0;
	dataTransferEnable = 1;
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, 5);
	ssd1306_WriteString("Export mode", Font_7x10, White);

	ssd1306_SetCursor(2, 40);
	ssd1306_WriteString("Press any key to return", Font_7x10, White);
	ssd1306_UpdateScreen();		//exportEnable
}

void dataControlMenuDefault() {
	switch (updownpointer) {
	case 0:
		ssd1306_SetCursor(10, 30);
		ssd1306_WriteString("   Login input    ", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;
	case 1:
		ssd1306_SetCursor(10, 30);
		ssd1306_WriteString("  Password input  ", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;
	case 2:
		ssd1306_SetCursor(10, 30);
		ssd1306_WriteString("     Delete       ", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;
	case 3:
		ssd1306_SetCursor(10, 30);
		ssd1306_WriteString("      Info        ", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;
	case 4:
		ssd1306_SetCursor(10, 30);
		ssd1306_WriteString(" Change password  ", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;
	case 5:
		ssd1306_SetCursor(10, 30);
		ssd1306_WriteString("      Back        ", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	}

}

void dataControlMenu() {
	/*
	 ssd1306_Fill(Black);
	 ssd1306_SetCursor(40,20);
	 ssd1306_WriteString(inn->url, Font_7x10, White);
	 ssd1306_SetCursor(40,30);
	 ssd1306_WriteString(inn->login, Font_7x10, White);
	 ssd1306_SetCursor(40,40);
	 ssd1306_WriteString(inn->password, Font_7x10, White);
	 ssd1306_UpdateScreen();
	 */
	menuStatus = 0;
	dataControlMenuStatus = 1;
	updownpointer = 0;
	ssd1306_Fill(Black);
	ssd1306_SetCursor(40, 3);
	ssd1306_WriteString(menu.blocks[menu.pointer].url, Font_7x10, White);
	ssd1306_Write_To_Bufer(2, 50, 8, 16, lt);
	ssd1306_Write_To_Bufer(120, 50, 8, 16, rt);
	dataControlMenuDefault();
}

void dataControlMenuDown() {
	updownpointer--;
	if (updownpointer < 0) {
		updownpointer = 5;

	}
	dataControlMenuDefault();
}

void dataControlMenuUp() {
	updownpointer++;
	if (updownpointer > 5) {
		updownpointer = 0;

	}
	dataControlMenuDefault();
}

void dataControlMenuSelect() {
	switch (updownpointer) {
	case 0:

		bufer[0] = 'l';
		bufer[1] = 'o';
		bufer[2] = 'g';
		bufer[3] = ':';
		memcpy(&bufer[4], menu.blocks[menu.pointer].login, 16);
		CDC_Transmit_FS(bufer, 20);
		break;
	case 1:

		bufer[0] = 'p';
		bufer[1] = 'a';
		bufer[2] = 's';
		bufer[3] = ':';
		memcpy(&bufer[4], menu.blocks[menu.pointer].password, 16);
		CDC_Transmit_FS(bufer, 20);
		break;
	case 2:
		menuStatus = 1;
		dataControlMenuStatus = 0;
		deleteData();

		break;
	case 3:
		//инфа
		//dataControlMenuStatus = 0;
		showDataInfo();
		break;
	case 4:
		//смена пароля
		changePasswordData();
		break;
	case 5:
		dataControlMenuStatus = 0;
		menuStatus = 1;
		updateScreen();
		break;
	}

}

void deleteData() {
	DataCount--;

	//menu.pointer = DataCount - 1;
	accauntBlock buf[DataCount];

	for (uint16_t i = menu.pointer + 1; i < DataCount + 1; i++) {
		char buf[64] = "abc";
		readFromEeprom(startaddressfordata + 64 * (i), buf, 64);
		writeToEeprom(startaddressfordata + 64 * (i - 1), buf, 64);
	}

	menu.pointer--;
	accauntBlock blocks[DataCount + 1];
	for (uint16_t i = 0; i < DataCount; i++) {
		char buf[64] = "";
		readFromEeprom(startaddressfordata + 64 * i, buf, 64);
		stringToStruct(&buf, &blocks[i]);
	}
	menu.blocks = blocks;
	menuStatus = 1;
	uploadDataCount();
	dataControlMenuStatus = 0;
	updateScreen();

}

void showDataInfo() {
	dataControlMenuStatus = 0;
	DataInfoMenu = 1;
	ssd1306_Fill(Black);
	ssd1306_SetCursor(30, 20);
	//ssd1306_WriteString("link: ", Font_7x10, White);
	ssd1306_WriteString((&menu.blocks[menu.pointer])->url, Font_7x10, White);
	//ssd1306_SetCursor(2, 120);
	//ssd1306_WriteString("        ", Font_7x10, White);
	ssd1306_SetCursor(30, 30);
	//ssd1306_WriteString("link: ", Font_7x10, White);
	ssd1306_WriteString((&menu.blocks[menu.pointer])->login, Font_7x10, White);
	ssd1306_SetCursor(30, 40);
	ssd1306_WriteString("Iteration: ", Font_7x10, White);
	ssd1306_WriteString(menu.blocks[menu.pointer].number, Font_7x10, White);
	ssd1306_UpdateScreen();
}

void stringToStruct(char *inn, accauntBlock *out) {
	memcpy(out->url, &inn[0], sizeof(out->url));
	memcpy(out->password, &inn[16], sizeof(out->password));
	memcpy(out->login, &inn[32], sizeof(out->login));
	memcpy(out->number, &inn[48], sizeof(out->number));
}

void structToString(accauntBlock *inn, char *out) {
	memcpy(&out[0], inn->url, sizeof(inn->url));
	memcpy(&out[16], inn->password, sizeof(inn->password));
	memcpy(&out[32], inn->login, sizeof(inn->login));
	memcpy(&out[48], inn->number, sizeof(inn->number));
}

void visualizeStruct(accauntBlock *inn) {
	ssd1306_Fill(Black);
	ssd1306_SetCursor(40, 30);
	ssd1306_WriteString(inn->url, Font_7x10, White);
	//ssd1306_SetCursor(40, 30);
	//ssd1306_WriteString(inn->login, Font_7x10, White);
	ssd1306_UpdateScreen();
	//HAL_Delay(100);
}

void writeToEeprom(uint16_t memoryAddres, uint8_t *data, uint16_t dataLength) {
	HAL_StatusTypeDef status;
	HAL_I2C_Mem_Write(&hi2c1, devAddr, memoryAddres, I2C_MEMADD_SIZE_16BIT,
			(uint8_t*) data, dataLength, HAL_MAX_DELAY);
	status = HAL_I2C_IsDeviceReady(&hi2c1, devAddr, 1, HAL_MAX_DELAY);
	while (status != HAL_OK) {
		status = HAL_I2C_IsDeviceReady(&hi2c1, devAddr, 1, HAL_MAX_DELAY);
	}
	//ssd1306_SetCursor(0,0);
	//ssd1306_WriteString(data, Font_7x10, White);
	// HAL_Delay(100);
}

void readFromEeprom(uint16_t memoryAddres, uint8_t *data, uint16_t dataLength) {
	HAL_StatusTypeDef status;
	HAL_I2C_Mem_Read(&hi2c1, devAddr, memoryAddres, I2C_MEMADD_SIZE_16BIT,
			(uint8_t*) data, dataLength, HAL_MAX_DELAY);
	status = HAL_I2C_IsDeviceReady(&hi2c1, devAddr, 1, HAL_MAX_DELAY);
	while (status != HAL_OK) {
		status = HAL_I2C_IsDeviceReady(&hi2c1, devAddr, 1, HAL_MAX_DELAY);
	}
	//ssd1306_SetCursor(0,20);
	//ssd1306_WriteString(data, Font_7x10, White);
	// HAL_Delay(100);

}

