#include "Adc.h"

#define ADCL   (*(volatile unsigned char*)0x78) 
#define ADCH   (*(volatile unsigned char*)0x79)  
#define ADC    (*(volatile unsigned short*)0x78) 

#define ADMUX (*(volatile unsigned char*)0x7C)

#define MUX0 0
#define MUX1 1
#define MUX2 2
#define MUX3  3

#define ADLAR 5
#define REFS0  6
#define REFS1  7

#define ADCSRA (*(volatile unsigned char*)0x7A)

#define ADPS0 0
#define ADPS1 1
#define ADPS2 2
#define ADIE  3
#define ADIF  4
#define ADATE 5
#define ADSC  6
#define ADEN  7


void Adc_Init(void)
{
    // AREF = AVcc
    ADMUX = (1<<REFS0);
 
    // ADC Enable and prescaler of 128
    // 16000000/128 = 125000
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

unsigned short Adc_ReadChannel(unsigned char ch)
{

  // select the corresponding channel 0~7
  // ANDing with ’7′ will always keep the value
  // of ‘ch’ between 0 and 7
  ch = ch & 0b00000111;  // AND operation with 7
  ADMUX = (ADMUX & 0b11111000)|ch; // clears the bottom 3 bits before ORing
 
  // start single convertion
  // write ’1′ to ADSC
  ADCSRA = ADCSRA | (1<<ADSC);
 
  // wait for conversion to complete
  // ADSC becomes ’0′ again
  // till then, run loop continuously
  while(ADCSRA & (1<<ADSC));
 
  return (ADC);

}
