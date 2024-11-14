// Include Guard to avoid multiple inclusion
#ifndef __adc__
#define __adc__

// Define ADC data registers
#define ADCL   (*(volatile unsigned char*)0x78) // Low byte of ADC result
#define ADCH   (*(volatile unsigned char*)0x79) // High byte of ADC result
#define ADC    (*(volatile unsigned short*)0x78) // ADC result (combined high + low bytes)

// Define ADC configuration registers
#define ADMUX (*(volatile unsigned char*)0x7C) // ADC Multiplexer Selection Register
#define ADCSRA (*(volatile unsigned char*)0x7A) // ADC Control and Status Register A

// Define ADC channel selection bits (used in ADMUX)
#define MUX0 0 // Channel selection bit 0
#define MUX1 1 // Channel selection bit 1
#define MUX2 2 // Channel selection bit 2
#define MUX3 3 // Channel selection bit 3

// Define ADMUX register bits
#define ADLAR 5 // Left-adjust ADC result
#define REFS0 6 // Reference selection bit 0
#define REFS1 7 // Reference selection bit 1

// Define ADCSRA register bits for ADC control
#define ADPS0 0 // ADC prescaler select bit 0
#define ADPS1 1 // ADC prescaler select bit 1
#define ADPS2 2 // ADC prescaler select bit 2
#define ADIE  3 // ADC Interrupt Enable
#define ADIF  4 // ADC Interrupt Flag
#define ADATE 5 // ADC Auto Trigger Enable
#define ADSC  6 // ADC Start Conversion
#define ADEN  7 // ADC Enable

// Function to initialize the ADC
void Adc_Init(void);

uint16_t adc_reading; // Variable to store ADC reading
// Function to read a specific ADC channel
uint16_t Adc_ReadChannel(uint8_t ch);

#endif
