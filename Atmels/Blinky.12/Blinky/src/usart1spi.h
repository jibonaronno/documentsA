/*
 * usart1spi.h
 *
 * Created: 9/18/2025 2:34:18 PM
 *  Author: tebun
 */ 

#include "usart_spi.h"

#ifndef USART1SPI_H_
#define USART1SPI_H_


#define USART_SERIAL                 USART1
#define USART_SERIAL_ID              ID_USART1  //USART0 for sam4l
#define USART_SERIAL_BAUDRATE        9600
#define USART_SERIAL_CHAR_LENGTH     US_MR_CHRL_8_BIT
#define USART_SERIAL_PARITY          US_MR_PAR_NO
#define USART_SERIAL_STOP_BIT        US_MR_NBSTOP_1_BIT

void usart1_init(void);
void usart1spi_init(void);

#endif /* USART1SPI_H_ */