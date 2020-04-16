
#include "data.h"

devAddr = (0x50 << 1);
startaddressfordata=0x1000;


void deviceIsntInit()
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2,2);
	ssd1306_WriteString("Start init from", Font_7x10, White);
	ssd1306_SetCursor(2,12);
		ssd1306_WriteString("your PC", Font_7x10, White);
	ssd1306_UpdateScreen();

}

void uploadIsInit()
{
	writeToEeprom(0x0000,&isInit ,1);
}

void downloadIsInit()
{
	readFromEeprom(0x0000, &isInit,1);
	ssd1306_SetCursor(2,2);
	ssd1306_WriteStringUint(isInit, Font_7x10, White);
	ssd1306_UpdateScreen();
}

void uploadSecureOpt()
{
	writeToEeprom(0x0000+1,&ProtectType ,1);
}

void downloadSecureOpt()
{
	readFromEeprom(0x0000+1, &ProtectType,1);
	ssd1306_SetCursor(12,2);
	ssd1306_WriteStringUint(ProtectType, Font_7x10, White);
	ssd1306_UpdateScreen();
}

void uploadPassword()
{
	writeToEeprom(0x0000+2,&password ,6);
}

void downloadPassword()
{
	readFromEeprom(0x0000+2, &password,6);
	ssd1306_SetCursor(12,50);
	ssd1306_WriteStringUint(password[0], Font_7x10, White);
	ssd1306_WriteStringUint(password[1], Font_7x10, White);
	ssd1306_WriteStringUint(password[2], Font_7x10, White);
	ssd1306_WriteStringUint(password[3], Font_7x10, White);
	ssd1306_WriteStringUint(password[4], Font_7x10, White);
	ssd1306_UpdateScreen();
}

void uploadPCIDcount()
{
	writeToEeprom(0x0000+8,&M5PPCIDCount ,1);
}

void downloadPCIDcount()
{
	readFromEeprom(0x0000+8, &M5PPCIDCount,1);
	ssd1306_SetCursor(22,2);
	ssd1306_WriteStringUint(M5PPCIDCount, Font_7x10, White);
	ssd1306_UpdateScreen();
}

void uploadDataCount()
{
	writeToEeprom(0x0000+9,&DataCount ,1);
}

void downloadDataCount()
{
	readFromEeprom(0x0000+9, &DataCount,1);
	ssd1306_SetCursor(32,2);
	ssd1306_WriteStringUint(DataCount, Font_7x10, White);
	ssd1306_UpdateScreen();
}


void uploadPCIDmas()
{
	//writeToEeprom(0x0000,&isInit ,1);
}

void downloadPCIDmas()
{
	//readFromEeprom(0x0000, &isInit,1);
	//ssd1306_SetCursor(2,20);
	//ssd1306_WriteStringUint(isInit, Font_7x10, White);
	//ssd1306_UpdateScreen();
}






uint8_t  lt[] =
{

	0B00000001,
	0B00000011,
	0B00000111,
	0B00001111,
	0B00011111,
	0B00111111,
	0B01111111,
	0B11111111,
	0B11111111,
	0B01111111,
	0B00111111,
	0B00011111,
	0B00001111,
	0B00000111,
	0B00000011,
	0B00000001
};



uint8_t rt[] =
{

	0B10000000,
	0B11000000,
	0B11100000,
	0B11110000,
	0B11111000,
	0B11111100,
	0B11111110,
	0B11111111,
	0B11111111,
	0B11111110,
	0B11111100,
	0B11111000,
	0B11110000,
	0B11100000,
	0B11000000,
	0B10000000
};


uint8_t cancel[] =
{

	0B10000001,
	0B01000010,
	0B00100100,
	0B00011000,
	0B00011000,
	0B00100100,
	0B01000010,
	0B10000001
};

uint8_t ok[] =
{

	0B00000000,
	0B00000001,
	0B00000010,
	0B00000100,
	0B10001000,
	0B01010000,
	0B00100000,
	0B00000000
};

uint8_t line[] =
{

	0B00000000,
	0B11111111,
	0B00000000,
	0B00000000,
	0B00000000,
	0B00000000,
	0B00000000,
	0B00000000
};



uint8_t linebold[] =
{

	0B00000000,
	0B11111111,
	0B11111111,
	0B00000000,
	0B00000000,
	0B00000000,
	0B00000000,
	0B00000000
};

uint8_t  upwd[] =
{

	0B00000000,0B00000000,
	0B00000000,0B00000000,
	0B00000000,0B00000000,
	0B00000001,0B10000000,
	0B00000011,0B11000000,
	0B00000111,0B11100000,
	0B00001111,0B11110000,
	0B00011111,0B11111000

};

uint8_t  downwd[] =
{
		0B00011111,0B11111000,
		0B00001111,0B11110000,
		0B00000111,0B11100000,
		0B00000011,0B11000000,
		0B00000001,0B10000000,
		0B00000000,0B00000000,
		0B00000000,0B00000000,
		0B00000000,0B00000000

};


uint8_t newDev[] =
{

	0B00000000,0B00000000,0B00000000,0B00000000,
	0B00000000,0B00000000,0B00000000,0B00000000,
	0B00001111,0B10000000,0B00000001,0B11110000,
	0B01111111,0B11111111,0B11111111,0B11111110,
	0B01000000,0B00000000,0B00000000,0B00000010,
	0B01000000,0B00000000,0B00000000,0B00000010,
	0B01000000,0B00000001,0B10000000,0B00000010,
	0B01000000,0B00000001,0B10000000,0B00000010,
	0B01000000,0B00000111,0B11100000,0B00000010,
	0B01000000,0B00000111,0B11100000,0B00000010,
	0B01000000,0B00000001,0B10000000,0B00000010,
	0B01000000,0B00000001,0B10000000,0B00000010,
	0B01000000,0B00000000,0B00000000,0B00000010,
	0B01000000,0B00000000,0B00000000,0B00000010,
	0B01111111,0B11111111,0B11111111,0B11111110,
	0B00000000,0B00000000,0B00000000,0B00000000
};

uint8_t restoreDev[] =
{

		0B00000000,0B00000000,0B00000000,0B00000000,
		0B00000000,0B00000000,0B00000000,0B00000000,
		0B00001111,0B10000000,0B00000001,0B11110000,
		0B01111111,0B11111111,0B11111111,0B11111110,
		0B01000000,0B00000001,0B00000000,0B00000010,
		0B01000000,0B00000011,0B00000000,0B00000010,
		0B01000000,0B00000111,0B10000000,0B00000010,
		0B01000000,0B00000011,0B01000000,0B00000010,
		0B01000000,0B00000001,0B00100000,0B00000010,
		0B01000000,0B00001000,0B00100000,0B00000010,
		0B01000000,0B00000100,0B01000000,0B00000010,
		0B01000000,0B00000011,0B10000000,0B00000010,
		0B01000000,0B00000000,0B00000000,0B00000010,
		0B01000000,0B00000000,0B00000000,0B00000010,
		0B01111111,0B11111111,0B11111111,0B11111110,
		0B00000000,0B00000000,0B00000000,0B00000000
};

uint8_t gear[] ={
	0B00000000, 0B00000001,0B10000000, 0B00000000,
	0B00000000, 0B00000011,0B11000000, 0B00000000,
	0B00000000, 0B00000111,0B11100000, 0B00000000,
	0B00011110, 0B00001111,0B11110000, 0B01111000,
	0B00011111, 0B10011110,0B01111001, 0B11111000,
	0B00011111, 0B11111100,0B00111111, 0B11111000,
	0B00011111, 0B11100000,0B00000111, 0B11111000,
	0B00001111, 0B00000000,0B00000000, 0B11111000,
	0B00001110, 0B00000111,0B11100000, 0B01110000,
	0B00000110, 0B00001110,0B01110000, 0B01100000,
	0B00000110, 0B00011000,0B00011000, 0B01100000,
	0B00001100, 0B00110000,0B00001100, 0B00110000,
	0B00011100, 0B01100001,0B10000110, 0B00111000,
	0B00111100, 0B11000011,0B11000011, 0B00111100,
	0B01111001, 0B10000111,0B11100001, 0B10011110,
	0B11110001, 0B10001110,0B01110001, 0B10011111,
	0B11110001, 0B10001110,0B01110001, 0B10011111,
	0B01111001, 0B10000111,0B11100001, 0B10011110,
	0B00111100, 0B11000011,0B11000011, 0B00111100,
	0B00011100, 0B01100001,0B10000110, 0B00111000,
	0B00001100, 0B00110000,0B00001100, 0B00110000,
	0B00000110, 0B00011000,0B00011000, 0B01100000,
	0B00000110, 0B00001110,0B01110000, 0B01100000,
	0B00001110, 0B00000111,0B11100000, 0B01110000,
	0B00001111, 0B00000000,0B00000000, 0B11111000,
	0B00011111, 0B11100000,0B00000111, 0B11111000,
	0B00011111, 0B11111100,0B00111111, 0B11111000,
	0B00011111, 0B10011110,0B01111001, 0B11111000,
	0B00011110, 0B00001111,0B11110000, 0B01111000,
	0B00000000, 0B00000111,0B11100000, 0B00000000,
	0B00000000, 0B00000011,0B11000000, 0B00000000,
	0B00000000, 0B00000001,0B10000000, 0B00000000

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

void initConstants()
{
	isInit=0;
	ProtectType=0;
	settingsMenuStatus=0;
	dataControlMenuStatus=0;
	DataCount=0;
	initStatus=0;
	initStatusStep1=0;
	initStatusStep2=0;
	restoreStatusStep1=0;
	restoreStatusStep2=0;
	menuStatus=0;
	restoreStatus=0;
	setPasswordStatus=0;
	settingsStatus=0;
	datasettingsStatus=0;
	setPasswordStep1=0;
	setPasswordStep2=0;

	setProtectTypeStep1=0;
	setProtectTypeStep2=0;
	passwordInputStatus=0;

	leftButtonStatus=0;
		rightButtonStatus=0;
		bothButtonStatus=0;

		M5PCIDdefaultIsGetted=0;

		downloadIsInit();
		downloadSecureOpt();
		downloadPassword();
		downloadPCIDcount();
		downloadDataCount();
	sconstants.blockscount=DataCount;
	//downloadPCIDmas();
	generatePassFrase();

}

void initChoseProcess()
{
	ssd1306_Fill(Black);
	ssd1306_Write_To_Bufer(16,24,32,16,newDev);
	ssd1306_Write_To_Bufer(80,24,32,16,restoreDev);
	ssd1306_UpdateScreen();
}

void initProcess1()
{
	initStatus=0;
	initStatusStep1=1;
	pointer=-1;
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2,5);
	ssd1306_WriteString("Write all 12 words in a safe place", Font_7x10, White);
	ssd1306_SetCursor(2,15);
	ssd1306_WriteString("into a safe place.", Font_7x10, White);
	ssd1306_SetCursor(2,25);
	ssd1306_WriteString("Press two buttons if you spelled the word", Font_7x10, White);
	ssd1306_SetCursor(2,35);
	ssd1306_WriteString("if you wrote word", Font_7x10, White);
	ssd1306_SetCursor(2,45);
	ssd1306_WriteString("or to continue.", Font_7x10, White);
	ssd1306_UpdateScreen();
	//char* passFrase[12];

}


void initProcess1Next()
{
	//Font_16x26  Font_11x18
	pointer++;
	if(pointer<12)
	{

	ssd1306_Fill(Black);
	ssd1306_SetCursor(40,10);
	char* text="Word ";
	//strcat(text, (char)(pointer+1));
	ssd1306_WriteString(text, Font_7x10, White);
	ssd1306_WriteStringUint((pointer+1), Font_7x10, White);
	ssd1306_SetCursor(25,25);
	ssd1306_WriteString(passFrase[pointer], Font_16x26, White);
	ssd1306_UpdateScreen();
	//char* passFrase[12];
	}
	else {
		//fCheckStatus=1;
		//initStatus=0;
		initStatusStep1=0;
			initStatusStep2=1;
		initProcess2();
	}

}

void initProcess2()
{

	pointer=-1;
	ssd1306_Fill(Black);
	ssd1306_SetCursor(15,10);
	ssd1306_WriteString("Check 4 random", Font_7x10, White);
	ssd1306_SetCursor(45,20);
	ssd1306_WriteString("words..", Font_7x10, White);
	ssd1306_Write_To_Bufer(2,54,8,8,cancel);
	ssd1306_Write_To_Bufer(120,54,8,8,ok);
	ssd1306_UpdateScreen();
	generateRandomNumbers(12,0xf);

}

void initProcess2Next()
{

	pointer++;
	if(pointer<4)
	{
	//uint16_t num;
	//num=HAL_RNG_GetRandomNumber(&hrng)&0x0000000F;
	ssd1306_Fill(Black);
	ssd1306_SetCursor(40,10);
		char* text="Word ";
		//strcat(text, (char)(pointer+1));
		ssd1306_WriteString(text, Font_7x10, White);
		ssd1306_WriteStringUint(RNGNumbers[pointer], Font_7x10, White);
		ssd1306_SetCursor(25,25);
		ssd1306_WriteString(passFrase[RNGNumbers[pointer]], Font_16x26, White);
		ssd1306_Write_To_Bufer(2,54,8,8,cancel);
		ssd1306_Write_To_Bufer(120,54,8,8,ok);
		ssd1306_UpdateScreen();
	}
	else {
		//fCheckStatus=1;
		//initStatus=0;
		initStatusStep2=0;
		setPasswordProcess1();
	}


}

void generateExtraData()
{
	isInit=1;
	uploadIsInit();
	uploadSecureOpt();
    uploadPassword();
	uploadPCIDcount();
	DataCount=0;
	sconstants.blockscount=DataCount;
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

void clearDevice()
{
	isInit=0;
	ProtectType=0;
	settingsMenuStatus=0;
	dataControlMenuStatus=0;
	DataCount=0;
	initStatus=0;
	initStatusStep1=0;
	initStatusStep2=0;
	restoreStatusStep1=0;
	restoreStatusStep2=0;
	menuStatus=0;
	restoreStatus=0;
	setPasswordStatus=0;
	settingsStatus=0;
	datasettingsStatus=0;
	setPasswordStep1=0;
	setPasswordStep2=0;
	setProtectTypeStep1=0;
	setProtectTypeStep2=0;
	passwordInputStatus=0;
	leftButtonStatus=0;
	rightButtonStatus=0;
	bothButtonStatus=0;
	M5PCIDdefaultIsGetted=0;
	uploadIsInit();
	uploadSecureOpt();
    uploadPassword();
	uploadPCIDcount();
	uploadDataCount();
	//uploadPCIDmas();


}




void restoreProcess1()
{
	initStatus=0;
	restoreStatusStep1=1;
	pointer=-1;

	ssd1306_Fill(Black);
	ssd1306_SetCursor(10,10);
	ssd1306_WriteString("Restore mode,", Font_7x10, White);
	ssd1306_SetCursor(10,20);
	ssd1306_WriteString("init your device", Font_7x10, White);
	ssd1306_SetCursor(10,30);
	ssd1306_WriteString("by using PC app", Font_7x10, White);
	ssd1306_SetCursor(10,50);
	ssd1306_WriteString("Press any key", Font_7x10, White);
	ssd1306_UpdateScreen();

}

void setPasswordProcess1()
{
	pointer=0;
		updownpointer=0;
		setPasswordStep1=1;
		ssd1306_Fill(Black);
		ssd1306_SetCursor(2,10);
		ssd1306_WriteString("Create password for device", Font_7x10, White);
		ssd1306_Write_To_Bufer(28,50,8,8,line);
		ssd1306_Write_To_Bufer(44,50,8,8,line);
		ssd1306_Write_To_Bufer(60,50,8,8,line);
		ssd1306_Write_To_Bufer(76,50,8,8,line);
		ssd1306_Write_To_Bufer(92,50,8,8,line);
		ssd1306_SetCursor(28+pointer*16,40);
		ssd1306_WriteStringUint(updownpointer, Font_7x10, White);
		ssd1306_Write_To_Bufer(28,50,8,8,linebold);
		ssd1306_UpdateScreen();


}



void setPasswordProcess1Next()
{
	password[pointer]=updownpointer;
	if(pointer<4)
	{
		ssd1306_Write_To_Bufer(28,50,8,8,line);
		ssd1306_Write_To_Bufer(44,50,8,8,line);
		ssd1306_Write_To_Bufer(60,50,8,8,line);
		ssd1306_Write_To_Bufer(76,50,8,8,line);
		ssd1306_Write_To_Bufer(92,50,8,8,line);
		pointer++;
		ssd1306_SetCursor(28+pointer*16,40);
	    ssd1306_WriteStringUint(updownpointer, Font_7x10, White);
		ssd1306_Write_To_Bufer(28+pointer*16,50,8,8,linebold);
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
	}
	else {
		//fCheckStatus=1;
		//initStatus=0;
		//generateandcheckPassword();
		setPasswordStep2=1;
		setPasswordStep1=0;
		setPasswordProcess2();
	}

}

void setPasswordProcess1Up()
{
	updownpointer++;
	if(updownpointer>9)
	{
		updownpointer=0;
	}

	ssd1306_SetCursor(28+(pointer)*16,40);
	ssd1306_WriteStringUint(updownpointer, Font_7x10, White);
	ssd1306_UpdateScreen();
}

void setPasswordProcess1Down()
{
	updownpointer--;
	if(updownpointer<0)
		{
			updownpointer=9;
		}
	ssd1306_SetCursor(28+(pointer)*16,40);
		ssd1306_WriteStringUint(updownpointer, Font_7x10, White);
		ssd1306_UpdateScreen();
}

void setPasswordProcess2()
{
	pointer=0;
		updownpointer=0;
		setPasswordStep2=1;
	ssd1306_Fill(Black);
			ssd1306_SetCursor(2,10);
			ssd1306_WriteString("Repeat password", Font_7x10, White);
			ssd1306_Write_To_Bufer(28,50,8,8,line);
			ssd1306_Write_To_Bufer(44,50,8,8,line);
			ssd1306_Write_To_Bufer(60,50,8,8,line);
			ssd1306_Write_To_Bufer(76,50,8,8,line);
			ssd1306_Write_To_Bufer(92,50,8,8,line);
			ssd1306_SetCursor(28+pointer*16,40);
			ssd1306_WriteStringUint(updownpointer, Font_7x10, White);
			ssd1306_Write_To_Bufer(28+pointer*16,50,8,8,linebold);
			ssd1306_UpdateScreen();

}

void  setPasswordProcess2Next()
{
	imputpassword[pointer]=updownpointer;
	if(pointer<4){

			ssd1306_Write_To_Bufer(28,50,8,8,line);
			ssd1306_Write_To_Bufer(44,50,8,8,line);
			ssd1306_Write_To_Bufer(60,50,8,8,line);
			ssd1306_Write_To_Bufer(76,50,8,8,line);
			ssd1306_Write_To_Bufer(92,50,8,8,line);

						pointer++;
			ssd1306_SetCursor(28+pointer*16,40);
		    ssd1306_WriteStringUint(updownpointer, Font_7x10, White);
			ssd1306_Write_To_Bufer(28+pointer*16,50,8,8,linebold);


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
		}
		else {
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
			if(passwordInputStatus==0)
			{
			if(imputpassword[0]==password[0]&&imputpassword[1]==password[1]&&imputpassword[2]==password[2]&&imputpassword[3]==password[3]&&imputpassword[4]==password[4])
			{

				setPasswordStep2=0;
				setProtectTypeProcess1();

			}
			else{
				setPasswordStep1=1;
							setPasswordStep2=0;
							password[0]=0;
								password[1]=0;
								password[2]=0;
								password[3]=0;
								password[4]=0;
								imputpassword[0]=0;
								imputpassword[1]=0;
								imputpassword[2]=0;
								imputpassword[3]=0;
								imputpassword[4]=0;
							setPasswordProcess1();
			}
			}
			else if(chpassComand==1)
			{

				if(imputpassword[0]==password[0]&&imputpassword[1]==password[1]&&imputpassword[2]==password[2]&&imputpassword[3]==password[3]&&imputpassword[4]==password[4])
								{
					                uploadPassword();
									setPasswordStep2=0;
									settingsMenuStatus=1;
									chpassComand=0;
									settingsMenu();
								}
				else{
									setPasswordStep2=0;
									setPasswordProcess1();
				}
			}
			else
			{
				if(imputpassword[0]==password[0]&&imputpassword[1]==password[1]&&imputpassword[2]==password[2]&&imputpassword[3]==password[3]&&imputpassword[4]==password[4])
				{
					setPasswordStep2=0;
					menuStatus=1;
				    initMenu();
			    }
				else
				{
					setPasswordProcess2();
				}
			}
		}
}

void setProtectTypeProcess1()
{
	setProtectTypeStep1=1;
	pointer=0;
	ssd1306_Fill(Black);
			ssd1306_SetCursor(2,10);
			ssd1306_WriteString("Choose secure mode", Font_7x10, White);
			ssd1306_Write_To_Bufer(56,30,16,8,upwd);
			ssd1306_Write_To_Bufer(56,50,16,8,downwd);
			switch(pointer)
						{
						case 0:
									ssd1306_SetCursor(10,39);
									ssd1306_WriteString("      none      ", Font_7x10, White);
									ssd1306_UpdateScreen();
									break;
						case 1:
									ssd1306_SetCursor(10,39);
									ssd1306_WriteString("    password    ", Font_7x10, White);
									ssd1306_UpdateScreen();
									break;
						case 2:
									ssd1306_SetCursor(10,39);
									ssd1306_WriteString("      PC ID     ", Font_7x10, White);
									ssd1306_UpdateScreen();
									break;
						case 3:
									ssd1306_SetCursor(10,39);
									ssd1306_WriteString("PC ID + password", Font_7x10, White);
									ssd1306_UpdateScreen();
									break;

						}
}

void setProtectTypeProcess1Next(){
	if(cProtectComand==1){
		ProtectType=pointer;
      uploadSecureOpt();
//			menuStatus=1;
			setProtectTypeStep1=0;
	//		initMenu();
			settingsMenuStatus=1;
			cProtectComand=0;
			settingsMenu();
	}else
	{
		ProtectType=pointer;
			generateExtraData();
			menuStatus=1;
			setProtectTypeStep1=0;
			initMenu();
	}

}
void setProtectTypeProcess1Up(){
	pointer++;
	if(pointer>3){
		pointer=0;

	}
	switch(pointer)
			{
			case 0:
						ssd1306_SetCursor(10,39);
						ssd1306_WriteString("      none      ", Font_7x10, White);
						ssd1306_UpdateScreen();
						break;
			case 1:
						ssd1306_SetCursor(10,39);
						ssd1306_WriteString("    password    ", Font_7x10, White);
						ssd1306_UpdateScreen();
						break;
			case 2:
						ssd1306_SetCursor(10,39);
						ssd1306_WriteString("      PC ID     ", Font_7x10, White);
						ssd1306_UpdateScreen();
						break;
			case 3:
						ssd1306_SetCursor(10,39);
						ssd1306_WriteString("PC ID + password", Font_7x10, White);
						ssd1306_UpdateScreen();
						break;

			}
}
void setProtectTypeProcess1Down(){
	pointer--;
	if(pointer<0){
		pointer=3;
	}
	switch(pointer)
			{
			case 0:
						ssd1306_SetCursor(10,39);
						ssd1306_WriteString("      none      ", Font_7x10, White);
						ssd1306_UpdateScreen();
						break;
			case 1:
						ssd1306_SetCursor(10,39);
						ssd1306_WriteString("    password    ", Font_7x10, White);
						ssd1306_UpdateScreen();
						break;
			case 2:
						ssd1306_SetCursor(10,39);
						ssd1306_WriteString("      PC ID     ", Font_7x10, White);
						ssd1306_UpdateScreen();
						break;
			case 3:
						ssd1306_SetCursor(10,39);
						ssd1306_WriteString("PC ID + password", Font_7x10, White);
						ssd1306_UpdateScreen();
						break;

			}
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
//settingsMenu;menu.pointer
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
		ssd1306_Write_To_Bufer(48,24,32,32,gear);
		ssd1306_UpdateScreen();
	}
}

void chooseMainMenu()
{
	if(menu.pointer==-1)
	{
		menuStatus=0;
		settingsMenu();
	}
	else
	{
		menuStatus=0;
		dataControlMenu(&menu.blocks[menu.pointer]);
	}
}

void settingsMenu()
{
	settingsMenuStatus=1;
	pointer=0;
		ssd1306_Fill(Black);
				ssd1306_SetCursor(20,5);
				ssd1306_WriteString("Settings", Font_7x10, White);
				ssd1306_Write_To_Bufer(56,30,16,8,upwd);
				ssd1306_Write_To_Bufer(56,50,16,8,downwd);
				switch(pointer)
								{
								case 0:
											ssd1306_SetCursor(10,39);
											ssd1306_WriteString("Change password ", Font_7x10, White);
											ssd1306_UpdateScreen();
											break;
								case 1:
											ssd1306_SetCursor(10,39);
											ssd1306_WriteString("  Reset device  ", Font_7x10, White);
											ssd1306_UpdateScreen();
											break;
								case 2:
											ssd1306_SetCursor(10,39);
											ssd1306_WriteString("  Export mode   ", Font_7x10, White);
											ssd1306_UpdateScreen();
											break;
								case 3:
											ssd1306_SetCursor(10,39);
											ssd1306_WriteString("Change Protection", Font_7x10, White);
											ssd1306_UpdateScreen();
											break;
								case 4:
																			ssd1306_SetCursor(10,39);
																			ssd1306_WriteString("      Back        ", Font_7x10, White);
																			ssd1306_UpdateScreen();
																			break;

								}
}

void settingsMenuUp()
{
	pointer++;
		if(pointer>4){
			pointer=0;

		}
		switch(pointer)
				{
				case 0:
							ssd1306_SetCursor(10,39);
							ssd1306_WriteString("Change password ", Font_7x10, White);
							ssd1306_UpdateScreen();
							break;
				case 1:
							ssd1306_SetCursor(10,39);
							ssd1306_WriteString("  Reset device  ", Font_7x10, White);
							ssd1306_UpdateScreen();
							break;
				case 2:
							ssd1306_SetCursor(10,39);
							ssd1306_WriteString("  Export mode   ", Font_7x10, White);
							ssd1306_UpdateScreen();
							break;
				case 3:
															ssd1306_SetCursor(10,39);
															ssd1306_WriteString("Change Protection", Font_7x10, White);
															ssd1306_UpdateScreen();
															break;
				case 4:
							ssd1306_SetCursor(10,39);
							ssd1306_WriteString("      Back        ", Font_7x10, White);
							ssd1306_UpdateScreen();
							break;

				}

}

void settingsMenuDown()
{
	pointer--;
		if(pointer<0){
			pointer=4;

		}
		switch(pointer)
		{
						case 0:
									ssd1306_SetCursor(10,39);
									ssd1306_WriteString("Change password ", Font_7x10, White);
									ssd1306_UpdateScreen();
									break;
						case 1:
									ssd1306_SetCursor(10,39);
									ssd1306_WriteString("  Reset device  ", Font_7x10, White);
									ssd1306_UpdateScreen();
									break;
						case 2:
									ssd1306_SetCursor(10,39);
									ssd1306_WriteString("  Export mode   ", Font_7x10, White);
									ssd1306_UpdateScreen();
									break;
						case 3:
																	ssd1306_SetCursor(10,39);
																	ssd1306_WriteString("Change Protection", Font_7x10, White);
																	ssd1306_UpdateScreen();
																	break;
						case 4:
									ssd1306_SetCursor(10,39);
									ssd1306_WriteString("      Back      ", Font_7x10, White);
									ssd1306_UpdateScreen();
									break;


						}

}

void settingsMenuSelect()
{
	switch(pointer)
			{
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
								settingsMenuStatus=0;
							    menuStatus=1;
							    updateScreen();
										break;

	}

}

void resetDeviceMenu()
{
	settingsMenuStatus=0;
	ResetComand=1;
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2,0);
	ssd1306_WriteString("Are you shure to ", Font_7x10, White);
	ssd1306_SetCursor(2,10);
	ssd1306_WriteString("reset device?", Font_7x10, White);
	ssd1306_Write_To_Bufer(2,54,8,8,cancel);
	ssd1306_Write_To_Bufer(120,54,8,8,ok);
	ssd1306_UpdateScreen();



}

void changeProtectionMenu()
{
	setProtectTypeStep1=1;
	cProtectComand=1;
	ssd1306_Fill(Black);
	setProtectTypeProcess1();
			ssd1306_UpdateScreen();



}

void passwordChangeMenu()
{
	settingsMenuStatus=0;
	setPasswordStep1=1;
	chpassComand=1;
		ssd1306_Fill(Black);
		setPasswordProcess1();
		ssd1306_UpdateScreen();
}

void exportModeMenu()
{
	settingsMenuStatus=0;
	exportEnable=1;
		ssd1306_Fill(Black);
		ssd1306_SetCursor(2,5);
		ssd1306_WriteString("Export mode", Font_7x10, White);

		ssd1306_SetCursor(2,40);
		ssd1306_WriteString("Press any key to return", Font_7x10, White);
		ssd1306_UpdateScreen();//exportEnable
}


void dataControlMenu(accauntBlock* inn)
{
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
	menuStatus=0;
	dataControlMenuStatus=1;
	updownpointer=0;
	ssd1306_Fill(Black);
	ssd1306_SetCursor(20,5);
	ssd1306_WriteString(inn->url, Font_7x10, White);
				ssd1306_Write_To_Bufer(56,30,16,8,upwd);
				ssd1306_Write_To_Bufer(56,50,16,8,downwd);
				switch(updownpointer)
								{
								case 0:
											ssd1306_SetCursor(10,39);
											ssd1306_WriteString("Login input ", Font_7x10, White);
											ssd1306_UpdateScreen();
											break;
								case 1:
											ssd1306_SetCursor(10,39);
											ssd1306_WriteString("  Password input  ", Font_7x10, White);
											ssd1306_UpdateScreen();
											break;
								case 2:
											ssd1306_SetCursor(10,39);
											ssd1306_WriteString("  Delete", Font_7x10, White);
											ssd1306_UpdateScreen();
											break;
								case 3:
											ssd1306_SetCursor(10,39);
											ssd1306_WriteString("      Info        ", Font_7x10, White);
											ssd1306_UpdateScreen();
											break;
								case 4:
																			ssd1306_SetCursor(10,39);
																			ssd1306_WriteString("      Back        ", Font_7x10, White);
																			ssd1306_UpdateScreen();
																			break;

								}
}


void dataControlMenuDown()
{
	updownpointer++;
		if(updownpointer>4){
			updownpointer=0;

		}
		switch(updownpointer)
										{
										case 0:
													ssd1306_SetCursor(10,39);
													ssd1306_WriteString("Login input ", Font_7x10, White);
													ssd1306_UpdateScreen();
													break;
										case 1:
													ssd1306_SetCursor(10,39);
													ssd1306_WriteString("  Password input  ", Font_7x10, White);
													ssd1306_UpdateScreen();
													break;
										case 2:
													ssd1306_SetCursor(10,39);
													ssd1306_WriteString("  Delete", Font_7x10, White);
													ssd1306_UpdateScreen();
													break;
										case 3:
													ssd1306_SetCursor(10,39);
													ssd1306_WriteString("      Info        ", Font_7x10, White);
													ssd1306_UpdateScreen();
													break;
										case 4:
																					ssd1306_SetCursor(10,39);
																					ssd1306_WriteString("      Back        ", Font_7x10, White);
																					ssd1306_UpdateScreen();
																					break;

										}

}

void dataControlMenuUp()
{
	updownpointer--;
		if(updownpointer<0){
			updownpointer=4;

		}
		switch(updownpointer)
										{
										case 0:
													ssd1306_SetCursor(10,39);
													ssd1306_WriteString("Login input ", Font_7x10, White);
													ssd1306_UpdateScreen();
													break;
										case 1:
													ssd1306_SetCursor(10,39);
													ssd1306_WriteString("  Password input  ", Font_7x10, White);
													ssd1306_UpdateScreen();
													break;
										case 2:
													ssd1306_SetCursor(10,39);
													ssd1306_WriteString("  Delete", Font_7x10, White);
													ssd1306_UpdateScreen();
													break;
										case 3:
													ssd1306_SetCursor(10,39);
													ssd1306_WriteString("      Info        ", Font_7x10, White);
													ssd1306_UpdateScreen();
													break;
										case 4:
																					ssd1306_SetCursor(10,39);
																					ssd1306_WriteString("      Back        ", Font_7x10, White);
																					ssd1306_UpdateScreen();
																					break;

										}

}

void dataControlMenuSelect()
{
	switch(updownpointer)
			{
							case 0:
								//passwordChangeMenu();
										break;
							case 1:
								//resetDeviceMenu();
										break;
							case 2:
								 //exportModeMenu();
										break;
							case 3:
								//exportModeMenu();
										break;
							case 4:
								dataControlMenuStatus=0;
							    menuStatus=1;
							    updateScreen();
										break;
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
