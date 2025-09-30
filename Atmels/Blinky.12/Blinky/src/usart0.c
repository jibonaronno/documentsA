/*
 * usart0.c
 *
 * Created: 9/25/2025 5:45:12 PM
 *
 * It is not USART rather UART or UART0. It is required to import UART module from ASF.
 * The board_init() function in init.c only use the function below to initialize UART0
 * #define PINS_UART0_MASK     (PIO_PA9A_URXD0 | PIO_PA10A_UTXD0)
 * #define PINS_UART0_PIO      PIOA
 * #define PINS_UART0_TYPE     PIO_PERIPH_A
 * #define PINS_UART0_ATTR     PIO_DEFAULT
 *...
 * void board_init(void)
 * {
 * ...
 * ...
 * pio_configure(PINS_UART0_PIO, PINS_UART0_TYPE, PINS_UART0_MASK, PINS_UART0_ATTR);
 * ...
 * }
 * 
 * Issues:
 * 1. Tx Speed is half from the settings value
 * 2. uart_write(...) function need to check if previous write is finished.
 *  
 */ 

#include <asf.h>
#include "uart.h"
#include "usart.h"
#include "usart0.h"

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif

void usart0_init(void)
{
	const sam_usart_opt_t usart_console_settings = {
		9600,
		US_MR_CHRL_8_BIT,
		US_MR_PAR_NO,
		US_MR_NBSTOP_1_BIT,
		US_MR_CHMODE_NORMAL,
		0
	};
	
	sam_uart_opt_t uart_console_settings;
	uart_console_settings.ul_baudrate = 9600;
	uart_console_settings.ul_mck = sysclk_get_main_hz();
	uart_console_settings.ul_mode = UART_MR_PAR_NO;
	
	#if SAM4L
	sysclk_enable_peripheral_clock(UART0);
	#else
	sysclk_enable_peripheral_clock(ID_UART0);
	pmc_enable_periph_clk(ID_UART0);
	#endif
	// usart_init_rs232(USART0, &usart_console_settings, sysclk_get_main_hz());
	uart_init(UART0, &uart_console_settings);
		
	uart_enable_tx(UART0);
	
	// usart_enable_tx(USART0);
	// usart_enable_rx(USART0);
}

#ifdef __cplusplus
}
#endif
