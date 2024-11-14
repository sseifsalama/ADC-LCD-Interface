// Include Guard to avoid multiple inclusion
#ifndef _dio_ 
#define _dio_

// Define PORTD register and related data direction and input registers
#define PORTD  (*(volatile unsigned char*)0x2B) // Data Register for PORTD
#define DDRD  (*(volatile unsigned char*)0x2A) // Data Direction Register for PORTD
#define PIND (*(volatile unsigned char*)0x29) // Input Pins Register for PORTD

// Define pins for PORTD
#define PD0 0
#define PD1 1
#define PD2 2
#define PD3 3
#define PD4 4
#define PD5 5
#define PD6 6
#define PD7 7

// Define PORTB register and related data direction and input registers
#define PORTB (*(volatile unsigned char*)0x25) // Data Register for PORTB
#define DDRB (*(volatile unsigned char*)0x24) // Data Direction Register for PORTB
#define PINB (*(volatile unsigned char*)0x23) // Input Pins Register for PORTB

// Define pins for PORTB
#define PB0 0
#define PB1 1
#define PB2 2
#define PB3 3
#define PB4 4
#define PB5 5

// Define PORTC register and related data direction and input registers
#define PORTC (*(volatile unsigned char*)0x28) // Data Register for PORTC
#define DDRC (*(volatile unsigned char*)0x27) // Data Direction Register for PORTC
#define PINC (*(volatile unsigned char*)0x26) // Input Pins Register for PORTC

// Define pins for PORTC
#define PC0 0
#define PC1 1
#define PC2 2
#define PC3 3
#define PC4 4
#define PC5 5

// Define pin directions and states
#define DIO_INPUT 0 // Set pin as input
#define DIO_OUTPUT 1 // Set pin as output
#define DIO_INPUT_PULLUP 2 // Set pin as input with pull-up resistor

// Define pin states
#define LOW 0 // Set pin to low
#define HIGH 1 // Set pin to high

// LCD Configuration
#define LCD_Dir  DDRD // Data direction register for LCD
#define LCD_Port PORTD // Data register for LCD
#define RS_EN_Dir  DDRD // Data direction register for RS and EN pins
#define RS_EN_Port PORTD // Data register for RS and EN pins

// Define LCD control pins
#define EN PD2 // Enable pin for LCD
#define RS PD3 // Register Select pin for LCD

// Define LED pin
#define RED_LED_PIN PC3 // Pin for red LED on PORTC

// Define keypad pins on PORTB
#define ROW1_PIN PB0 // Row 1 pin for keypad
#define ROW2_PIN PB1 // Row 2 pin for keypad
#define ROW3_PIN PB2 // Row 3 pin for keypad
#define COL1_PIN PB3 // Column 1 pin for keypad
#define COL2_PIN PB4 // Column 2 pin for keypad
#define COL3_PIN PB5 // Column 3 pin for keypad

// Define analog sensor pins
#define LDR_PIN PC0 // Pin for LDR sensor on PORTC
#define POT_PIN PC1 // Pin for potentiometer sensor on PORTC

// Function Declarations
void dio_init(void); // Initializes I/O
void Set_PIN_Direction(volatile uint8_t* ddr, uint8_t pin, uint8_t direction); // Sets pin direction
void Set_PIN_State(volatile uint8_t* port, uint8_t pin, uint8_t state); // Sets pin state (HIGH or LOW)
uint8_t Is_Button_Pressed(volatile uint8_t* pin_reg, uint8_t pin); // Checks if button is pressed

#endif
