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

volatile uint16_t  video_line=0;
volatile uint8_t   field=1;

//////////////////////////////////////////////////////////////// MAIN /////////////////////////////



int main(void)
{

	//IO
    DDRB = 0b00000010;  					//  b1 sound out
	DDRC = 0b00000000;  					//  c2 lightpen in
	DDRD = 0b11000000;  					//  d6,d7 video out,

	//Pull Up's / Outputs
	PORTB= 0b00000000; 						//
	PORTC= 0b00000000; 						//
	PORTD= 0b11000000;						//

	TCCR1A=0b00000000 ;						//configure timer 1 interrupt
	TCCR1B=0b00001101;						//ctc-mode, prescaler

	OCR1A=0;

	TIMSK= 0b00010100;						//Timer 1 , Bit 2  TOIE1: Timer/Counter1, Overflow Interrupt Enable
 	sei();									//switch on global interrupts

	while(1)
	{
	}

}


ISR(SIG_OUTPUT_COMPARE1A) 								// interrupt routine - each 64µS - generate video line signal -
{
	if (++video_line==305){

	    // V_SYNC:
		if (field==1){
			field=2;
			video_line=0;
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



		if (video_line>40 && video_line<284){
	        //image content
		 	for (uint8_t video_x=1;video_x<5; video_x++){
				GREY
				_delay_us(1);
				BLACK
				_delay_us(1);
			}
		}


		BLACK
	}
}



