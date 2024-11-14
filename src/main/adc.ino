#include "adc.h"

void Adc_Init(void) {
    // Set reference voltage to AVcc
    ADMUX = (1<<REFS0); // REFS0 = 1, which selects AVcc as the reference

    // Enable ADC and set prescaler to 128 (ADC clock = 16MHz / 128 = 125kHz)
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // ADEN = 1 enables ADC, ADPS2-0 set prescaler
}

uint16_t Adc_ReadChannel(uint8_t ch) {
    // Limit the input channel number to a value between 0 and 7
    ch = ch & 0b00000111;  // AND operation keeps only the last 3 bits, so max value is 7
    ADMUX = (ADMUX & 0b11111000) | ch; // Clear bottom 3 bits of ADMUX, then OR with channel number

    // Start a single conversion by setting ADSC bit to 1
    ADCSRA = ADCSRA | (1<<ADSC); // ADSC = 1 begins the ADC conversion
    
    // Wait for conversion to complete (ADSC bit will go back to 0 when done)
    while (ADCSRA & (1<<ADSC)); // Loop here until ADSC bit is cleared

    // Return the result from the ADC data register
    return (ADC); // ADC contains the 10-bit result from the conversion
}
