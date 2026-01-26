

#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <avr/pgmspace.h>


void uart_init();

void uart_putc(uint8_t c);

void uart_putc_hex(uint8_t b);
void uart_putw_hex(uint16_t w);
void uart_putdw_hex(uint32_t dw);

void uart_putw_dec(uint16_t w);
void uart_putdw_dec(uint32_t dw);

void uart_puts(const char* str);
void uart_puts_p(PGM_P str);

uint8_t uart_getc();
unsigned char uart_buffer_empty(void);


#endif

