/*
 * Project Blinky :
 * Primary Test Codes for initializing ATSAM4S16B chip and interfacing ST7735S 128x160 LCD from Microchip Studio for SAM devices.
 * LCD Interface is SPI and contains 2 more extra pins for RESET and A0 / DC / Data-Command Pin. Only MISO pin of SAM4S is used 
 * to send command and data to LCD. Other SPI Common pins SCK and CS are used by dedicated hardware pins. Exception is that USART1 
 * peripheral is used as SPI mode for this operation. Initially it is required to import the Libraries that support USART1 as SPI
 * Mode. Libraries are initially imported by using ASF Wizard. 
 * 1. Generic Board Support
 * 2. Delay Routines
 * 3. GPIO
 * 4. IOPORT
 * 5. SPI Serial Peripheral Interface Master usart_spi
 * 6. PIO
 * 7. SPI
 * 8. WDT
 * In Solution Explorer under src/config/conf_clock.h file contains Present clock frequency configuration.
 * Right now in this configuration the Serial Baud Rate is practically half of the configured baud rate. It 
 * may be required to change the clock config for proper frequency.
 * 
 * After importing the usart_spi Library from asf wizard the files are visible in Solution Explorer under
 * /src/ASF/common/services/sam_usart_spi/
 * The header file contains list of functions to start USART peripheral in SPI mode. This project uses USART1
 * peripheral in SPI mode and drive the LCD. 
 * PA22/TXD1 - LCD_MOSI
 * PA23/SCK1 - LCD_SCK
 * PA24/RTS1 - CS/NSS
 * PA19		 - LCD_D1/A0/DATA_COMMAND Pin of LCD
 * PA20		 - LCD_D2 / LCD RESET Pin
 * PA0		 - LCD_LED_PWM Pin
 * PB1		 - LCD POWER ON. Set this to Zero to turn on a P-Channel Mosfet.
 * 
 */

#include <asf.h>
#include "usart1spi.h"
#include "usart0.h"
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
	
	usart0_init();
	
	// LCD RESET AGAIN
	pio_set_output(PIOA, PIO_PA20, LOW, DISABLE, ENABLE); // HARD RESET LCD
	delay_ms(150);
	pio_set_output(PIOA, PIO_PA20, HIGH, DISABLE, ENABLE); // HARD RESET LCD FINISH
	
	delay_ms(150);
	
	//TFT_BlackTab_Initialize();
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
		
		//usart_putchar(USART0, 'H');
		//usart_putchar(USART0, 'E');
		//usart_putchar(USART0, '\n');
		
		uart_write(UART0, 'H');
		delay_ms(10);
		uart_write(UART0, 'a');
		delay_ms(10);
		uart_write(UART0, 'L');
		delay_ms(10);
		uart_write(UART0, 'O');
		delay_ms(10);
		uart_write(UART0, 'U');
		delay_ms(10);
		uart_write(UART0, '\r');
		delay_ms(10);
		uart_write(UART0, '\n');
		
		delay_ms(300);
		//pio_set_output(PIOA, PIO_PA0, LOW, DISABLE, ENABLE);
		//delay_ms(300);
		//pio_set_output(PIOA, PIO_PA0, HIGH, DISABLE, ENABLE);
	}
}
