/*
 * usart1spi.c
 *
 * Created: 9/18/2025 2:56:29 PM
 *  Author: tebun
 */ 
#include <asf.h>
#include "usart1spi.h"

void usart1_init(void)
{
	const sam_usart_opt_t usart_console_settings = {
		USART_SERIAL_BAUDRATE,
		USART_SERIAL_CHAR_LENGTH,
		USART_SERIAL_PARITY,
		USART_SERIAL_STOP_BIT,
		US_MR_CHMODE_NORMAL,
		0
	};
	
	#if SAM4L
	sysclk_enable_peripheral_clock(USART_SERIAL);
	#else
	sysclk_enable_peripheral_clock(USART_SERIAL_ID);
	pmc_enable_periph_clk(ID_USART1);
	#endif
	usart_init_rs232(USART_SERIAL, &usart_console_settings, sysclk_get_main_hz());
	//ioport_set_pin_dir(PIO_PA22_IDX, IOPORT_DIR_OUTPUT);
	usart_enable_tx(USART_SERIAL);
	// usart_enable_rx(USART_SERIAL);
}

void usart1spi_init(void)
{
	const sam_usart_opt_t usart_console_settings = {
		USART_SERIAL_BAUDRATE,
		USART_SERIAL_CHAR_LENGTH,
		USART_SERIAL_PARITY,
		USART_SERIAL_STOP_BIT,
		US_MR_CHMODE_NORMAL,
		0
	};
	
	struct usart_spi_device m_usart_spi_device;
	
	#if SAM4L
	sysclk_enable_peripheral_clock(USART_SERIAL);
	#else
	sysclk_enable_peripheral_clock(USART_SERIAL_ID);
	pmc_enable_periph_clk(ID_USART1);
	#endif
	
	usart_spi_setup_device(USART_SERIAL, &m_usart_spi_device, SPI_MODE_0, 50000, 0);
	usart_spi_init(USART_SERIAL);
	
	//usart_init_rs232(USART_SERIAL, &usart_console_settings, sysclk_get_main_hz());
	//ioport_set_pin_dir(PIO_PA22_IDX, IOPORT_DIR_OUTPUT);
	
	// usart_enable_tx(USART_SERIAL);
	// usart_enable_rx(USART_SERIAL);
}


