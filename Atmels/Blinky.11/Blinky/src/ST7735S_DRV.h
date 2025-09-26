/*
 * ST7735S_DRV.h
 *
 * Created: 9/19/2025 5:00:39 PM
 *  Author: tebun
 */ 


#ifndef ST7735S_DRV_H_
#define ST7735S_DRV_H_

#include "usart1spi.h"

#include <string.h>

#define _swap(a, b) { signed int16 t; t = a; a = b; b = t;}
#define _width         128
#define _height        160
#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09
#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13
#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_RAMRD   0x2E
#define ST7735_PTLAR   0x30
#define ST7735_VSCRDEF 0x33
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36
#define ST7735_VSCRSADD 0x37
#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6
#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5
#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD
#define ST7735_PWCTR6  0xFC
#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1
// Color definitions
#define   ST7735_BLACK   0x0000
#define   ST7735_BLUE    0x001F
#define   ST7735_RED     0xF800
#define   ST7735_GREEN   0x07E0
#define   ST7735_CYAN    0x07FF
#define   ST7735_MAGENTA 0xF81F
#define   ST7735_YELLOW  0xFFE0
#define   ST7735_WHITE   0xFFFF


#define TFT_DC_PIN		PIO_PA19
#define TFT_DC_PORT		PIOA
#define TFT_DC			TFT_DC_PIN
#define TFT_CS			PIO_PA24
#define TFT_DATA		PIO_PA22
#define TFT_CLK			PIO_PA23

#define TFT_SPI_HARDWARE

#define output_low(pin)		pio_set_output(TFT_DC_PORT, pin, LOW, DISABLE, ENABLE)
#define output_high(pin)	pio_set_output(TFT_DC_PORT, pin, HIGH, DISABLE, ENABLE)
// #define output_drive(pin)	

void spiwrite(uint8_t spidata);
void write_command(uint8_t cmd_);
void write_data(uint8_t data_);
void Bcmd();
void Rcmd1();
void Rcmd2green();
void Rcmd2red();
void Rcmd3();
void setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void drawPixel(uint8_t x, uint8_t y, uint16_t color);
void fillRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color);
void fillScreen(uint16_t color);
void drawFastVLine(uint8_t x, uint8_t y, uint8_t h, uint16_t color);
void drawFastHLine(uint8_t x, uint8_t y, uint8_t w, uint16_t color);
void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color);
void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color);
void drawRoundRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t r, uint16_t color);
void fillRoundRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t r, uint16_t color);
void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void drawChar(uint8_t x, uint8_t y, uint8_t c, uint16_t color, uint16_t bg,  uint8_t size);
void setTextWrap(int8_t w);
void drawtext(uint8_t x, uint8_t y, char *_text, uint16_t color, uint16_t bg, uint8_t size);
void DrawLineTest(void);
void invertDisplay(int8_t i);
void setScrollDefinition(uint8_t top_fix_height, uint8_t bottom_fix_height, int8_t _scroll_direction);
void VerticalScroll(uint8_t _vsp);
void NormalDisplay();
int16_t Color565(int16_t r, int16_t g, int16_t b);
void pushColor(int16_t color);
void TFT_GreenTab_Initialize();
void TFT_RedTab_Initialize();
void TFT_BlackTab_Initialize();
void TFT_ST7735B_Initialize();

void TFT_InitA();

#if defined (DRAW_BMP_FROM_MMCSD_CARD)                       // Additional code for drawing BMP image files from MMC/SD card
#ifndef pixel_buffer
#define pixel_buffer  10
#endif
int8_t bmpDraw(int8_t x, int8_t y, int8_t *bmpname);
#endif



#endif /* ST7735S_DRV_H_ */