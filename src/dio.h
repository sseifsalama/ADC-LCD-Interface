// Include Guard to avoid multiple inclusion
#ifndef _dio_ 
#define _dio_

// PORTD for 7 Segment
#define PIN_Segment_A 2
#define PIN_Segment_B 3
#define PIN_Segment_C 4
#define PIN_Segment_D 5
#define PIN_Segment_E 6
#define PIN_Segment_F 7

// PORTB for Other
#define PIN_Button_0 0
#define PIN_Button_1 1
#define PIN_Red_LED 2
#define PIN_Emergency_Button 3

#define DIO_INPUT 0
#define DIO_OUTPUT 1

#define LOW 0
#define HIGH 1

// Function Declarations
void Set_PIN_Direction(volatile uint8_t* ddr, uint8_t pin, uint8_t direction);
void Set_PIN_State(volatile uint8_t* port, uint8_t pin, uint8_t state);
void dio_init(void);
#endif