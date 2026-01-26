#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define OVERSAMPLES 10
volatile uint8_t timerOF=0;
static volatile uint16_t adcData;
static volatile uint16_t ADCtotal;
static volatile uint8_t adcDataL;
static volatile uint8_t adcDataH;
static volatile uint8_t sample_count;
inline ISR(TIMER0_OVF_vect){timerOF=1;}
inline ISR(ADC_vect)
{
    adcDataL = ADCL;
    adcDataH = ADCH;
    adcData = 0;
    adcData = adcData | adcDataH;
    adcData = adcData << 8;
    adcData = adcData | adcDataL;
    ADCtotal = ADCtotal+adcData;
    sample_count ++;
}
int16_t do_math(int16_t A,int16_t B,char operator)
{
    int32_t result = 0;
    if (operator == '+'){result = A+B;}
    if (operator == '-'){result = A-B;}
    if (operator == '*'){result = A*B;}
    if (operator == '/'){result = A/B;}
//    if (operator == '='){result = A = B;}
    int16_t i =  ((result >> 0) & 0xffff);
   return i;
}
uint16_t read_adc(uint8_t channel)
{
    ADMUX = ADMUX | channel;// set channel , by masking channel number to ADMUX
    ADCSRA |= (1<<ADEN); // enable the ADC
    sample_count = 0;//clear osample count
    ADCSRA |= (1<<ADSC);//start conversion
    //read adcData done in interrupt
    while (sample_count < OVERSAMPLES){asm volatile ("nop"::);}//wait for completion
    ADCSRA &=~ (1<<ADEN); // stop the ADC
    return (ADCtotal/OVERSAMPLES); //mx osamples = 63  othewise will overflow total register with 10 bit adc results
}
int main()
{
//set up ADC
    ADCSRA |= ( (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0) );//  sets adc clock prescaler to 128 //checked
    ADMUX |=  (1<<REFS0); // sets ref volts to Vcc 
    ADCSRA |= (1<<ADIE); // enable ADC conversion complete interrupt
    ADCSRA |= (1<<ADATE);// set to auto trigger (free running by default)
   DDRD |= (1<<5);
   DDRD |= (1<<6);
   DDRD |= (1<<7);
   DDRB |= (1<<0);
   DDRB |= (1<<1);
   DDRB |= (1<<2);
   DDRB |= (1<<3);
   DDRB |= (1<<4);
   DDRB |= (1<<5);

    //set up loop timer:
    TIMSK0 |= (1<<TOIE0);// overflow capture enable
    TCNT0 = 101;// start at this
    TCCR0B |= ((1<<CS10)|(1<<CS12));// timer started with /1024 prescaler 
 
   //setup timer for PWM  2
    DDRE |= (1<<5);
    TCCR3A |= ((1<<WGM30)|(1<<COM3C1));
    TCCR3B |= ((1<<WGM33)|(1<<CS30));
    OCR3C = 0 ;
    ICR3 = 500 ;

    sei();
    uint8_t cont_Name_1_NO = 0;
    uint16_t reg_ADC_Name_2 = 0;

    uint8_t Greater_2_6 = 0;
    uint8_t output_Name_1 = 0;
    uint8_t W = 1;
    while (1)
    {
        if (timerOF == 1)
        {
           timerOF=0;//reset timer flag
           TCNT0 = 101;// start at this
           //inputs:
             if(output_Name_1 == 1){
                cont_Name_1_NO=1;}
             else {
                cont_Name_1_NO=0;} //link name

            //Start of Ladder:
            //rung at 0
             W = 1;
             if(cont_Name_1_NO == 0){W = 0;}
            if (W == 1){OCR3C=500;}
            else{OCR3C= 0;}
            //end rung 

            //rung at 1
             W = 1;
            if (W == 1){reg_ADC_Name_2=read_adc(0);}
            else{reg_ADC_Name_2=0;}
            //end rung 

            //rung at 2
             W = 1;
             if(reg_ADC_Name_2 > 500){Greater_2_6=1;}
             else {Greater_2_6=0;} //comparison
             if(Greater_2_6 == 0){W = 0;}
              output_Name_1 = W;
            //end rung 

           //outputs:

       }
   }
}
