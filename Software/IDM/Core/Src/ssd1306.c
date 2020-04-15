
#include"ssd1306.h"


// Screenbuffer
static uint8_t SSD1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

// Screen object
static SSD1306_t SSD1306;


//
//  Send a byte to the command register
//
static void ssd1306_WriteCommand(uint8_t command)
{
	HAL_I2C_Mem_Write(&SSD1306_I2C_PORT, SSD1306_I2C_ADDR,0x00,1,&command,1,10);
}


//
//	Initialize the oled screen
//
uint8_t ssd1306_Init(void)
{	
	// Wait for the screen to boot
	HAL_Delay(100);
	
	/* Init LCD */
	ssd1306_WriteCommand(0xAE); //display off
	ssd1306_WriteCommand(0x20); //Set Memory Addressing Mode   
	ssd1306_WriteCommand(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	ssd1306_WriteCommand(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
	ssd1306_WriteCommand(0xC8); //Set COM Output Scan Direction
	ssd1306_WriteCommand(0x00); //---set low column address
	ssd1306_WriteCommand(0x10); //---set high column address
	ssd1306_WriteCommand(0x40); //--set start line address
	ssd1306_WriteCommand(0x81); //--set contrast control register
	ssd1306_WriteCommand(0xFF);
	ssd1306_WriteCommand(0xA1); //--set segment re-map 0 to 127
	ssd1306_WriteCommand(0xA6); //--set normal display
	ssd1306_WriteCommand(0xA8); //--set multiplex ratio(1 to 64)
	ssd1306_WriteCommand(0x3F); //
	ssd1306_WriteCommand(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	ssd1306_WriteCommand(0xD3); //-set display offset
	ssd1306_WriteCommand(0x00); //-not offset
	ssd1306_WriteCommand(0xD5); //--set display clock divide ratio/oscillator frequency
	ssd1306_WriteCommand(0xF0); //--set divide ratio
	ssd1306_WriteCommand(0xD9); //--set pre-charge period
	ssd1306_WriteCommand(0x22); //
	ssd1306_WriteCommand(0xDA); //--set com pins hardware configuration
	ssd1306_WriteCommand(0x12);
	ssd1306_WriteCommand(0xDB); //--set vcomh
	ssd1306_WriteCommand(0x20); //0x20,0.77xVcc
	ssd1306_WriteCommand(0x8D); //--set DC-DC enable
	ssd1306_WriteCommand(0x14); //
	ssd1306_WriteCommand(0xAF); //--turn on SSD1306 panel
	
	// Clear screen
	ssd1306_Fill(Black);
	
	// Flush buffer to screen
	ssd1306_UpdateScreen();
	
	// Set default values for screen object
	SSD1306.CurrentX = 0;
	SSD1306.CurrentY = 0;
	
	SSD1306.Initialized = 1;
	
	return 1;
}

//
//  Fill the whole screen with the given color
//
void ssd1306_Fill(SSD1306_COLOR color) 
{
	/* Set memory */
	uint32_t i;

	for(i = 0; i < sizeof(SSD1306_Buffer); i++)
	{
		SSD1306_Buffer[i] = (color == Black) ? 0x00 : 0xFF;
	}
}

//
//  Write the screenbuffer with changed to the screen
//
void ssd1306_UpdateScreen(void) 
{
	uint8_t i;
	
	for (i = 0; i < 8; i++) {
		ssd1306_WriteCommand(0xB0 + i);
		ssd1306_WriteCommand(0x00);
		ssd1306_WriteCommand(0x10);

		HAL_I2C_Mem_Write(&SSD1306_I2C_PORT, SSD1306_I2C_ADDR, 0x40, 1, &SSD1306_Buffer[SSD1306_WIDTH * i], SSD1306_WIDTH, 100);
	}
}

//
//	Draw one pixel in the screenbuffer
//	X => X Coordinate
//	Y => Y Coordinate
//	color => Pixel color
//
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color)
{
	if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) 
	{
		// Don't write outside the buffer
		return;
	}
	
	// Check if pixel should be inverted
	if (SSD1306.Inverted) 
	{
		color = (SSD1306_COLOR)!color;
	}
	
	// Draw in the right color
	if (color == White)
	{
		SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
	} 
	else 
	{
		SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
	}
}

//
//  Draw 1 char to the screen buffer
//	ch 		=> char om weg te schrijven
//	Font 	=> Font waarmee we gaan schrijven
//	color 	=> Black or White
//
char ssd1306_WriteChar(char ch, FontDef Font, SSD1306_COLOR color)
{
	uint32_t i, b, j;
	
	// Check remaining space on current line
	if (SSD1306_WIDTH <= (SSD1306.CurrentX + Font.FontWidth) ||
		SSD1306_HEIGHT <= (SSD1306.CurrentY + Font.FontHeight))
	{
		// Not enough space on current line
		return 0;
	}
	
	// Use the font to write
	for (i = 0; i < Font.FontHeight; i++)
	{
		b = Font.data[(ch - 32) * Font.FontHeight + i];
		for (j = 0; j < Font.FontWidth; j++)
		{
			if ((b << j) & 0x8000) 
			{
				ssd1306_DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR) color);
			} 
			else 
			{
				ssd1306_DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR)!color);
			}
		}
	}
	
	// The current space is now taken
	SSD1306.CurrentX += Font.FontWidth;
	
	// Return written char for validation
	return ch;
}

//
//  Write full string to screenbuffer
//
char ssd1306_WriteString(char* str, FontDef Font, SSD1306_COLOR color)
{
	// Write until null-byte
	while (*str) 
	{
		if (ssd1306_WriteChar(*str, Font, color) != *str)
		{
			// Char could not be written
			return *str;
		}
		
		// Next char
		str++;
	}
	
	// Everything ok
	return *str;
}

//
//	Position the cursor
//
void ssd1306_SetCursor(uint8_t x, uint8_t y) 
{
	SSD1306.CurrentX = x;
	SSD1306.CurrentY = y;
}


void ssd1306_Clear_Bufer_part(int x,int y,int width,int height)
	{
	for(int j=0;j<height;j++)
			{
				for(int i=0;i<width;i++)
				{

					ssd1306_DrawPixel(x+i, y+j, Black);
				}
			}
	}

	void ssd1306_Write_To_Bufer(int x,int y,int width,int height,const uint8_t* img)
	{
		for(int j=0;j<height;j++)
		{
			for(int i=0;i<width;i++)
			{
				if(((img[j*width/8+(i/8)]>>(7-i%8))&0b00000001)==1)
				ssd1306_DrawPixel(x+i, y+j, White);
				else ssd1306_DrawPixel(x+i, y+j, Black);
			}
		}
	}



	void ssd1306_WriteStringUint(uint16_t inn, FontDef Font, SSD1306_COLOR color)
	{
		if(inn==0)
		{
				ssd1306_WriteString("0", Font,color);

		}else{
		uint16_t count=0;
		uint16_t dev=1;
		uint16_t num=0;
		while(inn/dev!=0)
		{
			count++;
			dev*=10;
		}
		//count++;
		//dev=1000;

		dev=dev/10;

		for(uint16_t i=0;i<count;i++)
		{
			num=inn/dev;
			inn=inn%dev;
			dev=dev/10;
			switch(num)
			{
			case 1:
				ssd1306_WriteString("1", Font,color);
				break;
			case 2:
				ssd1306_WriteString("2", Font,color);
						break;
			case 3:
				ssd1306_WriteString("3", Font,color);
						break;
			case 4:
				ssd1306_WriteString("4", Font,color);
						break;
			case 5:
				ssd1306_WriteString("5", Font,color);
						break;
			case 6:
				ssd1306_WriteString("6", Font,color);
						break;
			case 7:
				ssd1306_WriteString("7", Font,color);
						break;
			case 8:
				ssd1306_WriteString("8", Font,color);
						break;
			case 9:
				ssd1306_WriteString("9", Font,color);
						break;
			case 0:
							ssd1306_WriteString("0", Font,color);
									break;
			}

		}
		}
	}


