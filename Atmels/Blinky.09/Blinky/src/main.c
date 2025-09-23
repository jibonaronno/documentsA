/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include "usart1spi.h"
#include "ST7735S_DRV.h"

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	
	/* Initialize the SAM system */
	SystemInit();

	board_init();

	/* Insert application code here, after the board has been initialized. */
	
	/** Disable Default Watchdog */
	wdt_init(WDT, WDT_MR_WDDIS, 0, 0);
	
	delay_init();
	
	char *text = "Hello World!";
	
	sysclk_enable_peripheral_clock(ID_PIOA);
	pmc_enable_periph_clk(ID_PIOA);
	ioport_set_pin_dir(PIO_PA0_IDX, IOPORT_DIR_OUTPUT);
	pio_set_output(PIOA, PIO_PA0, LOW, DISABLE, ENABLE);
	
	// LCD POWER 
	sysclk_enable_peripheral_clock(ID_PIOB);
	pmc_enable_periph_clk(ID_PIOB);
	ioport_set_pin_dir(PIO_PB1_IDX, IOPORT_DIR_OUTPUT);
	pio_set_output(PIOB, PIO_PB1, LOW, DISABLE, ENABLE);
	
	// LCD PINS INIT
	ioport_set_pin_dir(PIO_PA19_IDX, IOPORT_DIR_OUTPUT); // SIGNAL NAME LCD D1 . LCD PIN A0 . SELECT DATA / CMD . SET LOW TO CMD
	
	ioport_set_pin_dir(PIO_PA20_IDX, IOPORT_DIR_OUTPUT); // SIGNAL NAME LCD D2 . LCD PIN RESET. SET LOW TO RESET.

	ioport_set_pin_dir(PIO_PA24_IDX, IOPORT_DIR_OUTPUT); // PA24 NSS / CS for LCD
	
	pio_set_output(PIOA, PIO_PA20, LOW, DISABLE, ENABLE); // HARD RESET LCD
	delay_ms(50);
	pio_set_output(PIOA, PIO_PA20, HIGH, DISABLE, ENABLE); // HARD RESET LCD FINISH
	
	#ifndef TFT_SPI_HARDWARE
	ioport_set_pin_dir(PIO_PA22_IDX, IOPORT_DIR_OUTPUT); // LCD_MOSI / SDA for LCD
	ioport_set_pin_dir(PIO_PA23_IDX, IOPORT_DIR_OUTPUT); // LCD_SCK / SCK for LCD
	#endif
	
	delay_ms(150);
	
	//ioport_set_pin_dir(PIO_PA22_IDX, IOPORT_DIR_OUTPUT);
	//pio_set_output(PIOA, PIO_PA22, HIGH, DISABLE, ENABLE);
	
	pio_set_output(PIOA, PIO_PA0, LOW, DISABLE, ENABLE);
	delay_ms(1000);
	pio_set_output(PIOA, PIO_PA0, HIGH, DISABLE, ENABLE);
	
	#ifdef TFT_SPI_HARDWARE
		usart1spi_init();
	#else
		pio_set_output(PIOA, PIO_PA22, LOW, DISABLE, ENABLE);
		pio_set_output(PIOA, PIO_PA23, LOW, DISABLE, ENABLE);
	#endif
	
	
	// LCD RESET AGAIN
	pio_set_output(PIOA, PIO_PA20, LOW, DISABLE, ENABLE); // HARD RESET LCD
	delay_ms(150);
	pio_set_output(PIOA, PIO_PA20, HIGH, DISABLE, ENABLE); // HARD RESET LCD FINISH
	
	delay_ms(150);
	
	// TFT_BlackTab_Initialize();
	//TFT_RedTab_Initialize();
	TFT_InitA();
	delay_ms(150);
	
	uint8_t __x = 0;
	uint8_t __y = 0;
	
	fillScreen(ST7735_BLACK); // ST7735_BLACK); // ST7735_WHITE
	drawtext(28, 10, text, ST7735_YELLOW, ST7735_BLACK, 1);
	drawtext(28, 30, text, ST7735_RED, ST7735_BLACK, 3);
	
	while (1)
	{
		
		//usart_putchar(USART_SERIAL, '1');
		//usart_putchar(USART_SERIAL, '2');
		//usart_putchar(USART_SERIAL, '\n');
		
		//drawtext(19, 30, text, ST7735_RED, ST7735_BLACK, 3);
		
		drawPixel(__x, __y, ST7735_WHITE);
		
		if (__x < 100)
		{
			__x++;
			__y++;
		}
		else
		{
			__x = 0;
			__y = 0;
		}
		
		delay_ms(5);
		
		//usart_spi_write_single(USART_SERIAL, 55);
		
		// usart_putchar(USART_SERIAL, '\n');
	}
}
