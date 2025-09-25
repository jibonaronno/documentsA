/*
 * usart0.c
 *
 * Created: 9/25/2025 5:45:12 PM
 *  Author: tebun
 */ 

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
		115200,
		US_MR_CHRL_8_BIT,
		US_MR_PAR_NO,
		US_MR_NBSTOP_1_BIT,
		US_MR_CHMODE_NORMAL,
		0
	};
	
	#if SAM4L
	sysclk_enable_peripheral_clock(USART_SERIAL);
	#else
	sysclk_enable_peripheral_clock(ID_USART0);
	pmc_enable_periph_clk(ID_USART0);
	#endif
	usart_init_rs232(USART0, &usart_console_settings, sysclk_get_main_hz());
	//ioport_set_pin_dir(PIO_PA22_IDX, IOPORT_DIR_OUTPUT);
	usart_enable_tx(USART0);
	usart_enable_rx(USART0);
}

#ifdef __cplusplus
}
#endif
