#include "dio.h"

void dio_init(void) {
  
    // Initialize LCD pins as output
    Set_PIN_Direction(&DDRD, EN, DIO_OUTPUT); // Set EN pin as output
    Set_PIN_Direction(&DDRD, RS, DIO_OUTPUT); // Set RS pin as output
    Set_PIN_Direction(&DDRD, PD4, DIO_OUTPUT); // Set data pin PD4 as output
    Set_PIN_Direction(&DDRD, PD5, DIO_OUTPUT); // Set data pin PD5 as output
    Set_PIN_Direction(&DDRD, PD6, DIO_OUTPUT); // Set data pin PD6 as output
    Set_PIN_Direction(&DDRD, PD7, DIO_OUTPUT); // Set data pin PD7 as output

    // Initialize keypad pins
    Set_PIN_Direction(&DDRB, ROW1_PIN, DIO_OUTPUT); // Set ROW1 as output
    Set_PIN_Direction(&DDRB, ROW2_PIN, DIO_OUTPUT); // Set ROW2 as output
    Set_PIN_Direction(&DDRB, ROW3_PIN, DIO_OUTPUT); // Set ROW3 as output
    Set_PIN_Direction(&DDRB, COL1_PIN, DIO_INPUT_PULLUP); // Set COL1 as input with pull-up
    Set_PIN_Direction(&DDRB, COL2_PIN, DIO_INPUT_PULLUP); // Set COL2 as input with pull-up
    Set_PIN_Direction(&DDRB, COL3_PIN, DIO_INPUT_PULLUP); // Set COL3 as input with pull-up

    // Initialize PORTC pins
    Set_PIN_Direction(&DDRC, LDR_PIN, DIO_INPUT); // Set LDR pin as input
    Set_PIN_Direction(&DDRC, POT_PIN, DIO_INPUT); // Set potentiometer pin as input
    Set_PIN_Direction(&DDRC, PC2, DIO_INPUT); // Set PC2 as input (not specified, assumed for sensor)
    Set_PIN_Direction(&DDRC, RED_LED_PIN, DIO_OUTPUT); // Set red LED pin as output
    Set_PIN_Direction(&DDRC, PC4, DIO_OUTPUT); // Set PC4 as output (usage not specified)
    Set_PIN_Direction(&DDRC, PC5, DIO_OUTPUT); // Set PC5 as output (usage not specified)
}

void Set_PIN_Direction(volatile uint8_t* ddr, uint8_t pin, uint8_t direction) {
    if (pin >= 8) return; // Ignore invalid pin numbers
    else if (direction == DIO_INPUT) {
        *ddr &= ~(1 << pin); // Clear the bit to set pin as input
    } 
    else if (direction == DIO_OUTPUT) {
        *ddr |= (1 << pin); // Set the bit to make pin an output
    }
    else if (direction == DIO_INPUT_PULLUP) {
        *ddr &= ~(1 << pin); // Set pin as input
        PORTB |= (1 << pin); // Enable pull-up resistor
    }
}

void Set_PIN_State(volatile uint8_t* port, uint8_t pin, uint8_t state) {
    if (pin >= 8) return; // Ignore invalid pin numbers
    else if (state == HIGH) {
        *port |= (1 << pin); // Set the pin to HIGH
    } 
    else if (state == LOW) {
        *port &= ~(1 << pin); // Set the pin to LOW
    }
}

uint8_t Is_Button_Pressed(volatile uint8_t* pin_reg, uint8_t pin) {
    if (pin >= 8) return; // Ignore invalid pin numbers
    return !(*pin_reg & (1 << pin)); // Check if button is pressed (pin is LOW)
}
