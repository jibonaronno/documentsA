/*
LUMENOISE - LIGHTPEN CONTROLLED AV SYNTH

Licensed under:
----------------------------------------------------------------------------
"THE BEER-WARE LICENSE" (Revision 42):
<nikl@s-roy.de> wrote this file. As long as you retain this notice you
can do whatever you want with this stuff. If we meet some day, and you think
this stuff is worth it, you can buy me a beer in return Niklas Roy.
----------------------------------------------------------------------------

This code runs on an ATmega8 with 16MHz crystal
See Lumenoise Datasheet @ nilasroy.com for Hardware setup
*/
#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>
#include <math.h>
#include <avr/interrupt.h>

#define nop() 		asm volatile ("nop")

#define TRABANT		PORTD= 0b00000000;\
					_delay_us(2.5);\
					PORTD= 0b01000000;\
					_delay_us(29.5);

#define SYNC_IMPULS	PORTD= 0b00000000;\
					_delay_us(27);\
					PORTD= 0b01000000;\
					_delay_us(5);

#define ULTRABLACK	  PORTD= 0b00000000; // 0V
#define BLACK         PORTD= 0b01000000; //.2V
#define GREY          PORTD= 0b10000000; //.3V
#define WHITE         PORTD= 0b11000000; //.6V
#define LIGHTPEN 	  ( PINC & 0b00000100 )

uint16_t  	video_line=0;
uint8_t   	video_y;
uint8_t   	field=1;

uint8_t   	pen=0;
uint8_t 	pen_x=0;
uint8_t 	pen_y=0;
uint8_t 	pen_xt=0;
uint8_t 	pen_yt=0;
uint8_t 	crsr_x=0;
uint16_t 	crsr_y1=0;
uint16_t 	crsr_y2=0;
uint16_t 	crsr_y1t=0;
uint16_t 	crsr_y2t=0;
uint16_t 	blk_y1=50;
uint16_t 	blk_y2=50;

volatile uint8_t x;
volatile uint8_t y;

//////////////////////////////////////////////////////////////// MAIN /////////////////////////////



int main(void)
{

	//IO
    DDRB = 0b00001000;  					//  b3 sound out
	DDRC = 0b00000000;  					//  c2 lightpen in
	DDRD = 0b11000000;  					//  d6,d7 video out,

	//Pull Up's / Outputs
	PORTB= 0b00000000; 						//
	PORTC= 0b00000000; 						//
	PORTD= 0b11000000;						//

	TCCR1A=0b00000000;						//configure timer 1 interrupt for video timing
	TCCR1B=0b00001101;						//ctc-mode, prescaler

	TCCR2= 0b00011100;						//timer2 sound output,  PWM, Phase Correct
											//Toggle OC2 on Compare Match
											//clkT2S/1024 (From prescaler)

	OCR1A=0;

	TIMSK= 0b00010100;						//Timer 1 , Bit 2  TOIE1: Timer/Counter1, Overflow Interrupt Enable
 	sei();									//switch on global interrupts

	while(1)
	{
		if (y) OCR2=y;

	}
}


ISR(SIG_OUTPUT_COMPARE1A) 								// interrupt routine - each 64µS - generate video line signal -
{

	if (++video_line==305){

	    // V_SYNC:
		if (field==1){
			field=2;
			video_line=0;
			crsr_x=pen_x-1;
			crsr_y1=pen_y;
			crsr_y2=pen_y+6;
			blk_y1=pen_y-8;
			blk_y2=pen_y+14;
			pen_x=0;
			pen_y=0;
			cli(); //switch off global interrupts

				//-- 623
				ULTRABLACK
				_delay_us(4.7);
				BLACK
				_delay_us(27.3);

				ULTRABLACK
				_delay_us(2.35);
				BLACK
				_delay_us(29.65);

				//-- 624
				ULTRABLACK
				_delay_us(2.35);
				BLACK
				_delay_us(29.65);
				ULTRABLACK
				_delay_us(2.35);
				BLACK
				_delay_us(29.65);

				//-- 625
				ULTRABLACK
				_delay_us(2.35);
				BLACK
				_delay_us(29.65);
				ULTRABLACK
				_delay_us(2.35);
				BLACK
				_delay_us(29.65);

				//-- 1
				ULTRABLACK
				_delay_us(27.3);
				BLACK
				_delay_us(4.7);
				ULTRABLACK
				_delay_us(27.3);
				BLACK
				_delay_us(4.7);

				//-- 2
				ULTRABLACK
				_delay_us(27.3);
				BLACK
				_delay_us(4.7);
				ULTRABLACK
				_delay_us(27.3);
				BLACK
				_delay_us(4.7);

				//-- 3
				ULTRABLACK
				_delay_us(27.3);
				BLACK
				_delay_us(4.7);
				ULTRABLACK
				_delay_us(2.35);
				BLACK
				_delay_us(29.65);

				//-- 4
				ULTRABLACK
				_delay_us(2.35);
				BLACK
				_delay_us(29.65);
				ULTRABLACK
				_delay_us(2.35);
				BLACK
				_delay_us(29.65);

				//-- 5
				ULTRABLACK
				_delay_us(2.35);
				BLACK
				_delay_us(29.65);
				ULTRABLACK
				_delay_us(2.35);
				BLACK
				_delay_us(29.65);

			sei();
		}else{
			field=1;
			video_line=0;
			crsr_x=pen_x-1;
			crsr_y1t=pen_y;
			crsr_y2t=pen_y+6;
			blk_y1=pen_y-8;
			blk_y2=pen_y+14;
			pen_xt=0;
			pen_yt=0;

			cli();//switch off global interrupts

				//-- 311
				ULTRABLACK
				_delay_us(2.35);
				BLACK
				_delay_us(29.65);
				ULTRABLACK
				_delay_us(2.35);
				BLACK
				_delay_us(29.65);

				//-- 312
				ULTRABLACK
				_delay_us(2.35);
				BLACK
				_delay_us(29.65);
				ULTRABLACK
				_delay_us(2.35);
				BLACK
				_delay_us(29.65);

				//-- 313
				ULTRABLACK
				_delay_us(2.35);
				BLACK
				_delay_us(29.65);
				ULTRABLACK
				_delay_us(27.3);
				BLACK
				_delay_us(4.7);

				//-- 314
				ULTRABLACK
				_delay_us(27.3);
				BLACK
				_delay_us(4.7);
				ULTRABLACK
				_delay_us(27.3);
				BLACK
				_delay_us(4.7);

				//-- 315
				ULTRABLACK
				_delay_us(27.3);
				BLACK
				_delay_us(4.7);
				ULTRABLACK
				_delay_us(27.3);
				BLACK
				_delay_us(4.7);

				//-- 316
				ULTRABLACK
				_delay_us(2.35);
				BLACK
				_delay_us(29.65);
				ULTRABLACK
				_delay_us(2.35);
				BLACK
				_delay_us(29.65);

				//-- 317
				ULTRABLACK
				_delay_us(2.35);
				BLACK
				_delay_us(29.65);
				ULTRABLACK
				_delay_us(2.35);
				BLACK
				_delay_us(29.65);


			sei();
			}
	}else{
	    //H_SYNC:
		ULTRABLACK
		_delay_us(4.7);
		BLACK
		_delay_us(5.8);

		_delay_us(4);

		if (video_line>40 && video_line<284){
			video_y=video_line-40;

	        //image content

		 	for (uint8_t video_x=1;video_x<14; video_x++){
				GREY

				WHITE

				//draw cursor
			    if(video_x==crsr_x ){
					if(video_y>crsr_y1){
						if(video_y<crsr_y2){
							BLACK nop();
						}else{nop();}
					}else{nop();nop();nop();nop();nop();nop();nop();nop();}
				}else{nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();}

				//lightpen detected for first time
				if (pen_y==0){
					if(LIGHTPEN){
						pen_y=video_y+4;nop();nop();
					}else{nop();nop();nop();}
				}else{nop();nop();nop();nop();nop();nop();nop();}

				WHITE

				//few video lines below lightpen detected for first time
				if(pen_y==video_y){
					if(pen_x==0){
						if(LIGHTPEN){
							pen_x=video_x;
						}else{nop();}
					}else{nop();nop();nop();}
				}else{nop();nop();nop();nop();nop();nop();nop();nop();nop();}
			}
		}

		BLACK
		x=pen_x;
		y=pen_y;

	}
}



