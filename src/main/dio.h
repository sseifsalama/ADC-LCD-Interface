// Include Guard to avoid multiple inclusion
#ifndef _dio_ 
#define _dio_

#define PORTD  (*(volatile unsigned char*)0x2B)
#define DDRD  (*(volatile unsigned char*)0x2A)

#define PD0 0
#define PD1 1
#define PD2 2
#define PD3 3
#define PD4 4
#define PD5 5
#define PD6 6
#define PD7 7

#define PORTB (*(volatile unsigned char*)0x25)
#define DDRB (*(volatile unsigned char*)0x24)

#define PB0 0
#define PB1 1
#define PB2 2
#define PB3 3
#define PB4 4
#define PB5 5

#define DIO_INPUT 0
#define DIO_OUTPUT 1

#define LOW 0
#define HIGH 1

// Function Declarations

void Set_PIN_Direction(volatile uint8_t* ddr, uint8_t pin, uint8_t direction);
void Set_PIN_State(volatile uint8_t* port, uint8_t pin, uint8_t state);
void dio_init(void);

#endif