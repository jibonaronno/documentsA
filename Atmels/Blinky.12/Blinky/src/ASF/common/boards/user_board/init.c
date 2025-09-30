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

#define PIN_USART0_TXD_FLAGS		(PIO_PERIPH_A | PIO_DEFAULT)
#define PIN_USART0_RXD_FLAGS		(PIO_PERIPH_A | PIO_DEFAULT)

// UART config
#define PINS_UART0_MASK     (PIO_PA9A_URXD0 | PIO_PA10A_UTXD0)
#define PINS_UART0_PIO      PIOA
#define PINS_UART0_TYPE     PIO_PERIPH_A
#define PINS_UART0_ATTR     PIO_DEFAULT


//uint32_t pio_configure_pin(uint32_t ul_pin, const uint32_t ul_flags)


void board_init(void)
{
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
	gpio_configure_pin(PIO_PA22_IDX, PIN_USART1_TXD_FLAGS);
	gpio_configure_pin(PIO_PA21_IDX, PIN_USART1_RXD_FLAGS);
	gpio_configure_pin(PIO_PA23_IDX, PIN_USART1_SPI_SCK_FLAGS);
	gpio_configure_pin(PIO_PA24_IDX, PIN_USART1_SPI_NSS_FLAGS); // Disable NSS / CS to control CS Pin Manually.
	
	
	// pio_configure_pin(PIO_PA10A_UTXD0, PIN_USART0_TXD_FLAGS); // PIO_PERIPH_A);
	// pio_configure_pin(PIO_PA9A_URXD0, PIN_USART0_RXD_FLAGS);  // PIO_PERIPH_A);
	
	// sysclk_enable_peripheral_clock(ID_PIOA);
	// pmc_enable_periph_clk(ID_PIOA);
	
	
	//pio_configure_pin(PINS_UART0_MASK, (PIO_PERIPH_A | PIO_DEFAULT));
	
	pio_configure(PINS_UART0_PIO, PINS_UART0_TYPE, PINS_UART0_MASK, PINS_UART0_ATTR);
	// pio_configure_pin_group(PIO_PA0, PINS_UART0_MASK, PINS_UART0_ATTR);
	
	// gpio_configure_pin(PIO_PA9_IDX, PIN_USART0_RXD_FLAGS);
	// gpio_configure_pin(PIO_PA10_IDX, PIN_USART0_TXD_FLAGS);
	
}
