
#include <stdio.h>
#include <stdint.h>


static volatile uint16_t adcData;
static volatile uint16_t ADCtotal;
static volatile uint8_t adcDataL;
static volatile uint8_t adcDataH;
static volatile uint8_t sample_count;

//interrupt for built-in adc reads the 2 abit #'s into one 16 bit
ISR(ADC_vect)
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

void adc_init(void)
{
    ADCSRA |= ( (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0) );//  sets adc clock prescaler to 128 //checked
    ADMUX |=  (1<<REFS0); // sets ref volts to Vcc 
    ADCSRA |= (1<<ADIE); // enable ADC conversion complete interrupt
    ADCSRA |= (1<<ADATE);// set to auto trigger (free running by default)
}

uint16_t read_adc(uint8_8 channel)
{
    sei();//set enable interrupts    
    ADMUX = ADMUX | channel;// set channel , by masking channel number to ADMUX
    ADCSRA |= (1<<ADEN); // enable the ADC
    sample_count = 0;//clear osample count
    ADCSRA |= (1<<ADSC);//start conversion     
    //read adcData done in interrupt
    while (sample_count < OVERSAMPLES){asm volatile ("nop"::);}//wait for completion
    ADCSRA &=~ (1<<ADEN); // stop the ADC
    return ADCtotal/OVERSAMPLES; //mx osamples = 63  othewise will overflow total register with 10 bit adc results
}




{

    // set PORTB as output
    DDRB = 0xFF;

    // set prescaler and enable ADC
    adc_init(ADC_PRESCALER_DIV128);

    // set voltage reference, mux input and right adjustment
    adc_set_admux(ADC_VREF_AVCC | ADC_MUX_ADC0 | ADC_ADJUSTMENT_RIGHT);

    adc_enable_autotrigger();
    adc_enable_interrupt();

    // start the first conversion starting the freerunning mode
    adc_start_conversion();

    cpu_irq_enable();

    // output MSB of average on PORTB.
    while (1) {
        PORTB = (read_global() >> 8);
    }
}


