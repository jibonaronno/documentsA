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

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	
	/* Initialize the SAM system */
	SystemInit();

	board_init();

	/* Insert application code here, after the board has been initialized. */
	
	delay_init();
	
	sysclk_enable_peripheral_clock(ID_PIOA);
	pmc_enable_periph_clk(ID_PIOA);
	ioport_set_pin_dir(PIO_PA0_IDX, IOPORT_DIR_OUTPUT);
	pio_set_output(PIOA, PIO_PA0, LOW, DISABLE, ENABLE);
	
	//ioport_set_pin_dir(PIO_PA22_IDX, IOPORT_DIR_OUTPUT);
	//pio_set_output(PIOA, PIO_PA22, HIGH, DISABLE, ENABLE);
	
	usart1spi_init();
	
	while (1)
	{
		//pio_set_output(PIOA, PIO_PA22, HIGH, DISABLE, ENABLE);
		pio_set_output(PIOA, PIO_PA0, HIGH, DISABLE, ENABLE);
		delay_ms(100);
		
		//pio_set_output(PIOA, PIO_PA22, LOW, DISABLE, ENABLE);
		pio_set_output(PIOA, PIO_PA0, LOW, DISABLE, ENABLE);
		delay_ms(100);
		
		//usart_putchar(USART_SERIAL, 'A');
		//usart_putchar(USART_SERIAL, 'a');
		//usart_putchar(USART_SERIAL, 'B');
		//usart_putchar(USART_SERIAL, 'C');
		//usart_putchar(USART_SERIAL, '1');
		//usart_putchar(USART_SERIAL, '2');
		//usart_putchar(USART_SERIAL, '\n');
		
		usart_spi_write_single(USART_SERIAL, 55);
		
		// usart_putchar(USART_SERIAL, '\n');
	}
}
