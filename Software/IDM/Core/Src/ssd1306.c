#include"ssd1306.h"

static uint8_t SSD1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

static SSD1306_t SSD1306;

static void ssd1306_WriteCommand(uint8_t command) {
	HAL_I2C_Mem_Write(&SSD1306_I2C_PORT, SSD1306_I2C_ADDR, 0x00, 1, &command, 1,
			10);
}

uint8_t ssd1306_Init(void) {

	HAL_Delay(100);

	ssd1306_WriteCommand(0xAE);
	ssd1306_WriteCommand(0x20);
	ssd1306_WriteCommand(0x10);
	ssd1306_WriteCommand(0xB0);
	ssd1306_WriteCommand(0xC8);
	ssd1306_WriteCommand(0x00);
	ssd1306_WriteCommand(0x10);
	ssd1306_WriteCommand(0x40);
	ssd1306_WriteCommand(0x81);
	ssd1306_WriteCommand(0xFF);
	ssd1306_WriteCommand(0xA1);
	ssd1306_WriteCommand(0xA6);
	ssd1306_WriteCommand(0xA8);
	ssd1306_WriteCommand(0x3F);
	ssd1306_WriteCommand(0xA4);
	ssd1306_WriteCommand(0xD3);
	ssd1306_WriteCommand(0x00);
	ssd1306_WriteCommand(0xD5);
	ssd1306_WriteCommand(0xF0);
	ssd1306_WriteCommand(0xD9);
	ssd1306_WriteCommand(0x22);
	ssd1306_WriteCommand(0xDA);
	ssd1306_WriteCommand(0x12);
	ssd1306_WriteCommand(0xDB);
	ssd1306_WriteCommand(0x20);
	ssd1306_WriteCommand(0x8D);
	ssd1306_WriteCommand(0x14);
	ssd1306_WriteCommand(0xAF);

	ssd1306_Fill(Black);

	ssd1306_UpdateScreen();

	SSD1306.CurrentX = 0;
	SSD1306.CurrentY = 0;

	SSD1306.Initialized = 1;

	return 1;
}

void ssd1306_Fill(SSD1306_COLOR color) {

	uint32_t i;

	for (i = 0; i < sizeof(SSD1306_Buffer); i++) {
		SSD1306_Buffer[i] = (color == Black) ? 0x00 : 0xFF;
	}
}

void ssd1306_UpdateScreen(void) {
	uint8_t i;

	for (i = 0; i < 8; i++) {
		ssd1306_WriteCommand(0xB0 + i);
		ssd1306_WriteCommand(0x00);
		ssd1306_WriteCommand(0x10);

		HAL_I2C_Mem_Write(&SSD1306_I2C_PORT, SSD1306_I2C_ADDR, 0x40, 1,
				&SSD1306_Buffer[SSD1306_WIDTH * i], SSD1306_WIDTH, 100);
	}
}

void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color) {
	if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) {

		return;
	}

	if (SSD1306.Inverted) {
		color = (SSD1306_COLOR) !color;
	}

	if (color == White) {
		SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
	} else {
		SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
	}
}

char ssd1306_WriteChar(char ch, FontDef Font, SSD1306_COLOR color) {
	uint32_t i, b, j;

	if (SSD1306_WIDTH <= (SSD1306.CurrentX + Font.FontWidth) ||
	SSD1306_HEIGHT <= (SSD1306.CurrentY + Font.FontHeight)) {

		return 0;
	}

	for (i = 0; i < Font.FontHeight; i++) {
		b = Font.data[(ch - 32) * Font.FontHeight + i];
		for (j = 0; j < Font.FontWidth; j++) {
			if ((b << j) & 0x8000) {
				ssd1306_DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i),
						(SSD1306_COLOR) color);
			} else {
				ssd1306_DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i),
						(SSD1306_COLOR) !color);
			}
		}
	}

	SSD1306.CurrentX += Font.FontWidth;

	return ch;
}

char ssd1306_WriteString(char *str, FontDef Font, SSD1306_COLOR color) {

	while (*str) {
		if (ssd1306_WriteChar(*str, Font, color) != *str) {

			return *str;
		}

		str++;
	}

	return *str;
}

void ssd1306_SetCursor(uint8_t x, uint8_t y) {
	SSD1306.CurrentX = x;
	SSD1306.CurrentY = y;
}

void ssd1306_Clear_Bufer_part(int x, int y, int width, int height) {
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {

			ssd1306_DrawPixel(x + i, y + j, Black);
		}
	}
}

void ssd1306_Write_To_Bufer(int x, int y, int width, int height,
		const uint8_t *img) {
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (((img[j * width / 8 + (i / 8)] >> (7 - i % 8)) & 0b00000001)
					== 1)
				ssd1306_DrawPixel(x + i, y + j, White);
			else
				ssd1306_DrawPixel(x + i, y + j, Black);
		}
	}
}

void ssd1306_WriteStringUint(uint16_t inn, FontDef Font, SSD1306_COLOR color) {
	if (inn == 0) {
		ssd1306_WriteString("0", Font, color);

	} else {
		uint16_t count = 0;
		uint16_t dev = 1;
		uint16_t num = 0;
		while (inn / dev != 0) {
			count++;
			dev *= 10;
		}

		dev = dev / 10;

		for (uint16_t i = 0; i < count; i++) {
			num = inn / dev;
			inn = inn % dev;
			dev = dev / 10;
			switch (num) {
			case 1:
				ssd1306_WriteString("1", Font, color);
				break;
			case 2:
				ssd1306_WriteString("2", Font, color);
				break;
			case 3:
				ssd1306_WriteString("3", Font, color);
				break;
			case 4:
				ssd1306_WriteString("4", Font, color);
				break;
			case 5:
				ssd1306_WriteString("5", Font, color);
				break;
			case 6:
				ssd1306_WriteString("6", Font, color);
				break;
			case 7:
				ssd1306_WriteString("7", Font, color);
				break;
			case 8:
				ssd1306_WriteString("8", Font, color);
				break;
			case 9:
				ssd1306_WriteString("9", Font, color);
				break;
			case 0:
				ssd1306_WriteString("0", Font, color);
				break;
			}

		}
	}
}
