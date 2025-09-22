/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

#define PIN_USART1_TXD_FLAGS		(PIO_PERIPH_A | PIO_DEFAULT)
#define PIN_USART1_RXD_FLAGS		(PIO_PERIPH_A | PIO_DEFAULT)

#define PIN_USART1_SPI_SCK_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
#define PIN_USART1_SPI_NSS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)

void board_init(void)
{
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
	gpio_configure_pin(PIO_PA22_IDX, PIN_USART1_TXD_FLAGS);
	gpio_configure_pin(PIO_PA21_IDX, PIN_USART1_RXD_FLAGS);
	gpio_configure_pin(PIO_PA23_IDX, PIN_USART1_SPI_SCK_FLAGS);
	
	// gpio_configure_pin(PIO_PA24_IDX, PIN_USART1_SPI_NSS_FLAGS); // Disable NSS / CS to control CS Pin Manually.
	
}
