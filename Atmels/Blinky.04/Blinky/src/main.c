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
	
	delay_init();
	
	char *text = "Hello World!";
	
	sysclk_enable_peripheral_clock(ID_PIOA);
	pmc_enable_periph_clk(ID_PIOA);
	ioport_set_pin_dir(PIO_PA0_IDX, IOPORT_DIR_OUTPUT);
	pio_set_output(PIOA, PIO_PA0, LOW, DISABLE, ENABLE);
	
	// LCD PINS INIT
	ioport_set_pin_dir(PIO_PA19_IDX, IOPORT_DIR_OUTPUT); // SIGNAL NAME LCD D1 . LCD PIN A0 . SELECT DATA / CMD . SET LOW TO CMD
	
	ioport_set_pin_dir(PIO_PA20_IDX, IOPORT_DIR_OUTPUT); // SIGNAL NAME LCD D2 . LCD PIN RESET. SET LOW TO RESET.

	ioport_set_pin_dir(PIO_PA24_IDX, IOPORT_DIR_OUTPUT); // PA24 NSS / CS for LCD
	
	pio_set_output(PIOA, PIO_PA20, LOW, DISABLE, ENABLE); // HARD RESET LCD
	delay_ms(50);
	pio_set_output(PIOA, PIO_PA20, HIGH, DISABLE, ENABLE); // HARD RESET LCD FINISH
	
	delay_ms(150);
	
	//ioport_set_pin_dir(PIO_PA22_IDX, IOPORT_DIR_OUTPUT);
	//pio_set_output(PIOA, PIO_PA22, HIGH, DISABLE, ENABLE);
	
	pio_set_output(PIOA, PIO_PA0, HIGH, DISABLE, ENABLE);
	delay_ms(1000);
	pio_set_output(PIOA, PIO_PA0, LOW, DISABLE, ENABLE);
	delay_ms(1000);
	pio_set_output(PIOA, PIO_PA0, HIGH, DISABLE, ENABLE);
	delay_ms(1000);
	pio_set_output(PIOA, PIO_PA0, LOW, DISABLE, ENABLE);
	delay_ms(1000);
	pio_set_output(PIOA, PIO_PA0, HIGH, DISABLE, ENABLE);
	
	usart1spi_init();
	
	delay_ms(1150);
	
	// TFT_BlackTab_Initialize();
	// TFT_RedTab_Initialize();
	TFT_InitA();
	delay_ms(1150);
	
	uint8_t __x = 0;
	uint8_t __y = 0;
	
	// fillScreen(ST7735_RED); // ST7735_BLACK); // ST7735_WHITE
	// drawtext(28, 10, text, ST7735_YELLOW, ST7735_BLACK, 2);
	
	while (1)
	{
		
		//usart_putchar(USART_SERIAL, '1');
		//usart_putchar(USART_SERIAL, '2');
		//usart_putchar(USART_SERIAL, '\n');
		
		//drawtext(19, 30, text, ST7735_RED, ST7735_BLACK, 3);
		drawPixel(__x, __y, ST7735_WHITE);
		
		__x++;
		__y++;
		delay_ms(200);
		
		//usart_spi_write_single(USART_SERIAL, 55);
		
		// usart_putchar(USART_SERIAL, '\n');
	}
}
