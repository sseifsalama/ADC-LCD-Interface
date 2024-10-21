#include <avr/io.h>
#include "dio.h"

void dio_init(void) {
    Set_PIN_Direction(&DDRD, PIN_Segment_A, DIO_OUTPUT);
    Set_PIN_Direction(&DDRD, PIN_Segment_B, DIO_OUTPUT);
    Set_PIN_Direction(&DDRD, PIN_Segment_C, DIO_OUTPUT);
    Set_PIN_Direction(&DDRD, PIN_Segment_D, DIO_OUTPUT);
    Set_PIN_Direction(&DDRD, PIN_Segment_E, DIO_OUTPUT);
    Set_PIN_Direction(&DDRD, PIN_Segment_F, DIO_OUTPUT);
  
    Set_PIN_Direction(&DDRB, PIN_Button_1, DIO_INPUT);
    Set_PIN_Direction(&DDRB, PIN_Button_0, DIO_INPUT);
    Set_PIN_Direction(&DDRB, PIN_Emergency_Button, DIO_INPUT);

    Set_PIN_Direction(&DDRB, PIN_Red_LED, DIO_OUTPUT);

    // Set all pins to HIGH to ensure proper operation
    for (uint8_t i = PIN_Segment_A; i <= PIN_Segment_F; i++) {
        Set_PIN_State(&PORTD, i, HIGH);
    }
    Set_PIN_State(&PORTB, PIN_Red_LED, HIGH);
    _delay_ms(1000);

    // Set all pins to LOW to ensure proper operation
    Set_PIN_State(&PORTB, PIN_Red_LED, LOW);
    for (uint8_t i = PIN_Segment_A; i <= PIN_Segment_F; i++) {
        Set_PIN_State(&PORTD, i, LOW);
    }

    // Display 0 on 7 Segment
    for (uint8_t i = PIN_Segment_A; i <= PIN_Segment_F; i++) {
        Set_PIN_State(&PORTD, i, HIGH);
    }
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