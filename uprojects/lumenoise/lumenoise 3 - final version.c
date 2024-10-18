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

#define SET_EOI_FLAG 	PORTB |= (1 << 1);       //set end of image flag
#define CLEAR_EOI_FLAG  PORTB &= ~(1 << 1);      //clear end of image flag
#define EOI_FLAG        PINB & ( 1 << 1 )        //read end of image flag

#define SET_POS_FLAG 	PORTB |= (1 << 2);       //set pen on screen flag
#define CLEAR_POS_FLAG  PORTB &= ~(1 << 2);      //clear pen on screen flag
#define POS_FLAG        PINB & ( 1 << 2 )        //read pen on screen flag
#define SPK_ON 	PORTB |= (1 << 3);       //speaker on
#define SPK_OFF PORTB &= ~(1 << 3);      //speaker off


#define LED_YELLOW PORTC= 0b00000010;
#define LED_RED    PORTC= 0b00000001;

uint16_t  	video_line=0;
uint8_t   	video_y;
uint8_t   	field=1;

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

uint8_t effect4_x;
uint8_t effect4_y;


uint8_t vis_freq; //visual frequency
uint8_t vis_amp;  //visual amplitude
uint8_t vis_spd;  //visual scrolling speed

uint8_t cnt0=0;
uint8_t cnt_spd=0;
uint8_t cnt1=0;
uint16_t lcnt0=0;
uint16_t lcnt1=0;
uint8_t cnt2;
uint32_t cnt3=0;
uint8_t val;

volatile uint16_t   vol_cntxchange=0b0010000000000000;
volatile uint8_t    vol_x;
volatile uint8_t 	vol_y;
volatile uint8_t    vol_blackbars=0;
volatile uint8_t    vol_sidebars=1;
volatile uint8_t    binarydisplay[16];

volatile uint8_t justdelay1=0;
volatile uint16_t justdelay2=0;


uint8_t old_x=255;


uint8_t effect1;//switches black bars on and off
uint8_t effect2;//switches sinewave on and off
uint8_t effect3;//switches sidebar on and off
uint8_t effect4;//switches antibar on and off


uint8_t pos_effect_cnt=0;
uint8_t nopos_effect_cnt=0;
uint8_t max_pos_effect=25;

uint8_t    vis_shift[65];
uint8_t	   grey[65]={	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
						5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
						5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
						5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};
uint8_t	   antibar[64];
uint8_t    title[35]={
						0b00011111,
						0b00010000,
						0b00000000,
						0b00011111,
						0b00010000,
						0b00011111,
						0b00000000,
						0b00011111,
						0b00000001,
						0b00011111,
						0b00000001,
						0b00011111,
						0b00000000,
						0b00011111,
						0b00010101,
						0b00010101,
						0b00000000,
						0b00011111,
						0b00000001,
						0b00011111,
						0b00000000,
						0b00011111,
						0b00010001,
						0b00011111,
						0b00000000,
						0b00011111,
						0b00000000,
						0b00010111,
						0b00010101,
						0b00011101,
						0b00000000,
						0b00011111,
						0b00010101,
						0b00010101,
						0b00000000
						};

volatile uint8_t  vol_startup=0;//set to 0
volatile uint8_t  vol_start=0;
volatile uint8_t  vol_starteffect=0;

uint8_t    max_bars=4; //maximum amount of bars
uint8_t    sfx=0;
uint8_t    pos_old=0;
uint16_t   t=0;

uint16_t   load_sine=0;
uint8_t tmp_ocr;

//predefined sinewave
uint8_t sine[256]=
	{
	127 , 130 , 133 , 136 , 139 , 142 , 145 , 148 , 151 , 154 , 157 , 160 , 163 , 166 , 169 , 172 ,
	175 , 178 , 181 , 184 , 186 , 189 , 192 , 194 , 197 , 200 , 202 , 205 , 207 , 209 , 212 , 214 ,
	216 , 218 , 221 , 223 , 225 , 227 , 229 , 230 , 232 , 234 , 235 , 237 , 239 , 240 , 241 , 243 ,
	244 , 245 , 246 , 247 , 248 , 249 , 250 , 250 , 251 , 252 , 252 , 253 , 253 , 253 , 253 , 253 ,
	254 , 253 , 253 , 253 , 253 , 253 , 252 , 252 , 251 , 250 , 250 , 249 , 248 , 247 , 246 , 245 ,
	244 , 243 , 241 , 240 , 239 , 237 , 235 , 234 , 232 , 230 , 229 , 227 , 225 , 223 , 221 , 218 ,
	216 , 214 , 212 , 209 , 207 , 205 , 202 , 200 , 197 , 194 , 192 , 189 , 186 , 184 , 181 , 178 ,
	175 , 172 , 169 , 166 , 163 , 160 , 157 , 154 , 151 , 148 , 145 , 142 , 139 , 136 , 133 , 130 ,
	126 , 123 , 120 , 117 , 114 , 111 , 108 , 105 , 102 , 99 , 96 , 93 , 90 , 87 , 84 , 81 , 78 ,
	75 , 72 , 69 , 67 , 64 , 61 , 59 , 56 , 53 , 51 , 48 , 46 , 44 , 41 , 39 , 37 , 35 , 32 , 30 ,
	28 , 26 , 24 , 23 , 21 , 19 , 18 , 16 , 14 , 13 , 12 , 10 , 9 , 8 , 7 , 6 , 5 , 4 , 3 , 3 , 2 ,
	1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 2 , 3 , 3 , 4 , 5 , 6 , 7 , 8 , 9 ,
	10 , 12 , 13 , 14 , 16 , 18 , 19 , 21 , 23 , 24 , 26 , 28 , 30 , 32 , 35 , 37 , 39 , 41 , 44 ,
	46 , 48 , 51 , 53 , 56 , 59 , 61 , 64 , 67 , 69 , 72 , 75 , 78 , 81 , 84 , 87 , 90 , 93 , 96 ,
	99 , 102 , 105 , 108 , 111 , 114 , 117 , 120 , 123
	 };

//////////////////////////////////////////////////////////////// MAIN /////////////////////////////



int main(void)
{

	//IO
    DDRB = 0b00001110;  					//  b1: end of image flag, b2: pen on screen flag, b3: sound out
	DDRC = 0b00000011;  					//  c0+1:bicolor led, c2 lightpen in
	DDRD = 0b11000000;  					//  d6,d7 video out,

	//Pull Up's / Outputs
	PORTB= 0b00000000; 						//
	PORTC= 0b00000000; 						//
	PORTD= 0b11000000;						//

	TCCR1A=0b00000000;						//configure timer 1 interrupt for video timing
	TCCR1B=0b00001101;						//ctc-mode, prescaler



	OCR1A=0;

	TIMSK= 0b00010100;						//Timer 1 , Bit 2  TOIE1: Timer/Counter1, Overflow Interrupt Enable
 	sei();									//switch on global interrupts

	while(1)    //mainloop
	{
		cnt1++;
		cnt3++;
		if (vol_start){

			if (vol_startup>150){
				TCCR2= 0b00011110;
				OCR2=255-vol_startup;
				_delay_us(150);
			} else if (vol_startup>10){
				TCCR2= 0b00011110;
				OCR2=cnt1;
				_delay_us(100);
			} else if (vol_startup<10){
				if (vol_starteffect){
					TCCR2= 0b00011100;
					OCR2=vol_starteffect*20;
					_delay_us(200);
				}else{
					TCCR2= 0b00000000;						//timer2 no sound output,
					OCR2=0;
					SPK_OFF //speaker off
				}
			}
		}

		if (POS_FLAG) {

				//pen on screen

			    LED_YELLOW
				lcnt0+=vol_x;
				lcnt1+=vol_y;

				if (vol_x!=old_x)vol_cntxchange++;

				t++;


				switch (vol_x){
					case 1:
						if(vol_sidebars){TCCR2=t;}else{TCCR2= 0b00011110;}
						OCR2=vol_y;
						if(load_sine>20)load_sine--;
					break;

					case 2:
						if(vol_sidebars){TCCR2=t;}else{TCCR2= 0b00011101;}
						OCR2=(t<<t/400 |  (t<<(t-100)/800)>>7  |  t<<-t/200)+vol_y ;
						if(OCR2==0)	{grey[vol_y/4-4]=1;t+=50;}
						t+=(vol_y/30-5);
						if(load_sine>20)load_sine--;
					break;

					case 3:
						if(vol_sidebars){TCCR2=t;}else{TCCR2= 0b00011101;}
						OCR2=sine[t>>10]+vol_y;
						t+=((180-vol_y));
						load_sine++;
					break;

					case 4:
						tmp_ocr = ((t/vol_y | -t/11) & 56<<1) ; //((t/500 | t/10) & 97) +vol_y;

						if (tmp_ocr+(cnt0/10)<24){

							if(vol_sidebars){TCCR2=t;}else{TCCR2= 0b00011111;}
							}

						if (tmp_ocr+(cnt0/10)>24){
							if(vol_sidebars){TCCR2=t;}else{TCCR2= 0b00011101;}
							}

						antibar[vol_y/4+4]=((cnt0>>6)+tmp_ocr)%3;

						OCR2=tmp_ocr+(vol_y/4);
						if(load_sine>20)load_sine--;
					break;

				}

				old_x=vol_x;

			} else {

				// no pen on screen
				LED_RED
				pos_old=0;
				TCCR2= 0b00000000;						//timer2 no sound output,
				OCR2=0;
				SPK_OFF //speaker off
			}

		if(antibar[60]&&!(cnt1%250))vol_cntxchange++;


		if (EOI_FLAG){

			//end of image; plenty of time for calculations

			CLEAR_EOI_FLAG
			cnt_spd=(t%20)-10;
			cnt0+=cnt_spd; //incr 8bit frame counter
			cnt2--;


			if ((vol_cntxchange>>8)&0b0000000000000001)  {effect1=1;}else{effect1=0;}
			if ((vol_cntxchange>>10)&0b0000000000000001)  {effect2=1;}else{effect2=0;}
			if ((vol_cntxchange>>12)&0b0000000000000001) {effect3=1;}else{effect3=0;}
			if ((vol_cntxchange>>14)&0b0000000000000001) {effect4=1;}else{effect4=0;}

			if (effect1){
				vol_blackbars=1;
				grey[63]=vol_x-1;
			} else {
				vol_blackbars=0;
			}

			if (effect3 && (vol_cntxchange>>1)&0b0000000000000001){
				vol_sidebars=1;
			}else{
				vol_sidebars=0;
			}

			antibar[0]=0;
			cnt1+=vol_y;
			if (effect4){
			    if(effect1){
					if(grey[0]<5)antibar[0]=vol_y+1; //blackbars reach top: create antibar
				}else{
					antibar[0]=vol_y*pos_old;
				}
			}

			vis_shift[64]=6;
			for (uint8_t i=0;i<64;i++){

				//precalc visual sineshift
				if(vol_x==3){
					uint16_t large_num=(abs(i-(vol_y/4)) * sine[((i*(255-OCR2)/10)+t/80+cnt2)%256]);
					large_num/=1000;
					large_num+=6-(abs(i-(vol_y/4))/11);

					vis_shift[i]=large_num;
					if(vis_shift[i]>12)vis_shift[i]=12;

				}else{

					if(load_sine>2000){
						if(load_sine>3000)load_sine=3000;
						uint16_t large_num = sine[(i*((t/1000)%20)+cnt0)%256];
						vis_shift[i]=large_num/21;
						if(vis_shift[i]>12)vis_shift[i]=12;

					}else{
						vis_shift[i]=6;
					}
				}

				//precalc black bars array
				grey[i]=grey[i+1];//0...maxbars


			}

			for (uint8_t i=64;i>0;i--){
				//precalc antibar array
				antibar[i]=antibar[i-1];
			}

		}
	}
}





ISR(SIG_OUTPUT_COMPARE1A) 								// interrupt routine - each 64µS - generate video line signal -
{

	if (++video_line==305){

	    // V_SYNC:
		if (field==1){
			field=2;
			video_line=0;

			if (pen_y&&!pen_x)pen_x=max_bars-1;
			crsr_x=pen_x-1;
			crsr_y1=pen_y-3;
			crsr_y2=pen_y+9;
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

			if (pen_y&&!pen_x)pen_x=max_bars-1;
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
		_delay_us(7.5);//min5.7


		if(vol_startup<250){
			vol_start=1;
			_delay_us(1);

		 	if(video_line==40){
				cnt0++;
				if (vol_startup)vol_startup+=2;
			}
			uint8_t shiftli=0;
			if(vol_startup>150) shiftli=vol_startup-150;
			if(!(vol_startup/2%2)){
				if(video_line>140 && video_line<160){
					video_y=video_line-35;

					_delay_us(1.6);
					for (uint8_t i=0;i<34;i++){	//lumenoise txt

						if(0b00000001&(title[i-shiftli]>>(video_y/2)%8)){WHITE}else{BLACK nop();}
					}
				}

				if(video_line>170&&video_line<212&&vol_startup<150){
					video_y=video_line-170;
					_delay_us(17);
					vol_starteffect=0;
					for(uint8_t i=0;i<5;i++){
						nop();
						if(i==(cnt0/2)%64){BLACK vol_starteffect=i; }else{WHITE vol_starteffect=0;}
					}
					BLACK
					for (uint8_t i=0;i<10;i++)if(LIGHTPEN&&!vol_startup) vol_startup++;
				}
			}
			BLACK;
			justdelay1++;
			if(justdelay1%2)justdelay2++;
		}else{
			vol_start=0;


			if (video_line>40 && video_line<284){
				video_y=video_line-40;

				//antibar

				if(antibar[video_y/4]){

				    uint8_t temp_bar=antibar[video_y/4];


					BLACK
					_delay_us(9);nop();nop();nop();nop();nop();nop();nop();nop();nop();

					for(uint8_t i=0;i<25;i++){
						BLACK nop();nop();nop();nop();nop();
						if(temp_bar>1){ WHITE nop();}else{ BLACK nop();nop();}

					}
					BLACK
					BLACK
				}else{
					//white bar on left side

					if(vol_sidebars){
						GREY
					}else{
						BLACK
						nop();nop();
					}
					_delay_us(5);

					//sinewave shift to right

					uint8_t loc_x_shift=vis_shift[video_y/4];
					for (uint8_t i=0;i<loc_x_shift;i++){nop();}

			        //image content

				 	for (uint8_t video_x=0;video_x<=max_bars; video_x++){
					nop();nop();nop();nop();nop();nop();
					    if(video_x<max_bars){
						    nop();nop();nop();nop();nop();nop();

							if(grey[video_y/4]!=video_x){BLACK WHITE}else{GREY BLACK}
						} else {
							nop();nop();nop();nop();nop();nop();nop();nop();WHITE BLACK
						}

						//few video lines below lightpen detected for first time (in order to find out precise x pos)
						if(pen_y==video_y){
							if(pen_x==0){
								if(LIGHTPEN){
									pen_x=video_x;
								}else{nop();}
							}else{nop();nop();nop();}
						}else{nop();nop();nop();nop();nop();nop();nop();nop();nop();}



						//draw cursor
					    if(video_x==crsr_x ){
							if(video_y>crsr_y1){
								if(video_y<crsr_y2){
								    GREY nop();nop();nop();nop();nop();

								}else{nop();nop();nop();nop();nop();}

							}else{nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();}

						}else{nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();}

						//lightpen detected for first time (determines y-pos)
						if (pen_y==0){
							if(LIGHTPEN){
								pen_y=video_y+4;
							}else{nop();}
						}else{nop();nop();nop();nop();nop();}



					    if(video_x<max_bars){
							if(grey[video_y/4]!=video_x){WHITE}else{BLACK}
						}else {
							BLACK
						}

						nop();nop();nop();nop();nop();nop();nop();nop();
					}


				}
			}else if (video_line==286){

				SET_EOI_FLAG //end of image flag

				if (vol_x==0&&vol_y==0){CLEAR_POS_FLAG}else{SET_POS_FLAG} //set|clear pen on screen flag



				vol_x=pen_x;
				vol_y=pen_y;

				if (pen_x==0&&pen_y==0){CLEAR_POS_FLAG}else{SET_POS_FLAG}

			}
		}
		BLACK
	}
}






