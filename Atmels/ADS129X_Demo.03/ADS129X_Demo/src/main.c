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

/**
 * @brief TMOUT Driver Document
 * @file TMOUT.c
 * @file TMOUT.h
 * conf_board.h contains constant definitions for TMOUT driver.
 * #define TC_TMOUT TC0
 * #define TC_TMOUT_CHN 0
 * #define TC_TMOUT_Handler TC0_Handler
 * #define ID_TC_TMOUT ID_TC0
 * #define TMOUT_BASE_FREQ_HZ  (100) 
 */

#include <asf.h>
#include "trismed/drivers/TMOUT.h"
#include "trismed/drivers/ADS129x.h"

/**
 *  Configure UART0 for debug message output. stdio printf support.
 *  CONF_UART is UART0 in user_board.h at the end and CONSOLE_UART_ID is ID_UART0 in user_board.h . 
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	/* Initialize the SAM system */
	SystemInit();
	board_init();
	/** Disable Default Watchdog */
	wdt_init(WDT, WDT_MR_WDDIS, 0, 0);
	sysclk_init();
	delay_init();
	
	TMOUT_Init();
	
	/* Configure UART for debug message output. */
	configure_console();
	
	ADS1298_ModuleInit();
	
	while (1)
	{
		printf("ADS1298_Test %d \r\n", 122);
		delay_ms(1000);
	}

	/* Insert application code here, after the board has been initialized. */
}
