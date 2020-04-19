#include "stm32f2xx_hal.h"
#include "fonts.h"

#ifndef ssd1306
#define ssd1306

#define SSD1306_I2C_PORT		hi2c1

#define SSD1306_I2C_ADDR        (0x3C << 1)

#define SSD1306_WIDTH           130

#define SSD1306_HEIGHT          64

typedef enum {
	Black = 0x00, White = 0x01
} SSD1306_COLOR;

typedef struct {
	uint16_t CurrentX;
	uint16_t CurrentY;
	uint8_t Inverted;
	uint8_t Initialized;
} SSD1306_t;

extern I2C_HandleTypeDef SSD1306_I2C_PORT;

uint8_t ssd1306_Init(void);
void ssd1306_Fill(SSD1306_COLOR color);
void ssd1306_UpdateScreen(void);
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);
char ssd1306_WriteChar(char ch, FontDef Font, SSD1306_COLOR color);
char ssd1306_WriteString(char *str, FontDef Font, SSD1306_COLOR color);
void ssd1306_SetCursor(uint8_t x, uint8_t y);

#endif
