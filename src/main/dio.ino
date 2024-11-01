
#include "dio.h"

void dio_init(void) {
    Set_PIN_Direction(&DDRD, PD4, DIO_OUTPUT);
    Set_PIN_Direction(&DDRD, PD5, DIO_OUTPUT);
    Set_PIN_Direction(&DDRD, PD6, DIO_OUTPUT);
    Set_PIN_Direction(&DDRD, PD7, DIO_OUTPUT);
  
}

void Set_PIN_Direction(volatile uint8_t* ddr, uint8_t pin, uint8_t direction) {
    if (pin >= 8) return; // Invalid pin
    else if (direction == DIO_INPUT) {
        *ddr &= ~(1 << pin); 
    } 
    else if (direction == DIO_OUTPUT) {
        *ddr |= (1 << pin);
    }
}

void Set_PIN_State(volatile uint8_t* port, uint8_t pin, uint8_t state) {
    if (pin >= 8) return; // Invalid pin
    else if (state == HIGH) {
        *port |= (1 << pin);
    } 
    else if (state == LOW) {
        *port &= ~(1 << pin);
    }
}