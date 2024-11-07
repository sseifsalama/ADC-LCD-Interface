// Include Guard to avoid multiple inclusion
#ifndef _dio_ 
#define _dio_

#define PORTD  (*(volatile unsigned char*)0x2B)
#define DDRD  (*(volatile unsigned char*)0x2A)
#define PIND (*(volatile unsigned char*)0x29)

// LCD Pins Port
#define LCD_Dir  DDRD
#define LCD_Port PORTD
#define RS_EN_Dir  DDRD
#define RS_EN_Port PORTD

// Pins (PORTD)
#define PD0 0
#define PD1 1
#define EN 2
#define RS 3
#define PD4 4
#define PD5 5
#define PD6 6
#define PD7 7

#define PORTB (*(volatile unsigned char*)0x25)
#define DDRB (*(volatile unsigned char*)0x24)
#define PINB (*(volatile unsigned char*)0x23)

// Keypad Pins (PORTB)
#define ROW1_PIN 0
#define ROW2_PIN 1
#define ROW3_PIN 2
#define COL1_PIN 3
#define COL2_PIN 4
#define COL3_PIN 5

#define PORTC (*(volatile unsigned char*)0x28)
#define DDRC (*(volatile unsigned char*)0x27)
#define PINC (*(volatile unsigned char*)0x26)

// Pins (PORTC)
#define PC0 0
#define PC1 1
#define PC2 2
#define PC3 3
#define PC4 4
#define PC5 5

#define DIO_INPUT 0
#define DIO_OUTPUT 1
#define DIO_INPUT_PULLUP 2

#define LOW 0
#define HIGH 1

// Function Declarations
void dio_init(void);
void Set_PIN_Direction(volatile uint8_t* ddr, uint8_t pin, uint8_t direction);
void Set_PIN_State(volatile uint8_t* port, uint8_t pin, uint8_t state);
uint8_t Is_Button_Pressed(volatile uint8_t* pin_reg, uint8_t pin);

#endif