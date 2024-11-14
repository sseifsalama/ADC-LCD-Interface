#include "keypad.h"
#include "dio.h"

char keypad_get_key(void) {
    // Iterate over each row to detect key press
    for (int row = 0; row < 3; row++) {
        // Set all rows high initially (no row selected)
        Set_PIN_State(&PORTB, ROW1_PIN, HIGH);
        Set_PIN_State(&PORTB, ROW2_PIN, HIGH);
        Set_PIN_State(&PORTB, ROW3_PIN, HIGH);
        
        // Pull only the current row low to check it
        Set_PIN_State(&PORTB, ROW1_PIN + row, LOW);

        // Short delay to allow signals to settle
        _delay_us(5);

        // Check each column to see if a button in this row is pressed
        if (Is_Button_Pressed(&PINB, COL1_PIN)) return key_map[row][0]; // Column 1
        if (Is_Button_Pressed(&PINB, COL2_PIN)) return key_map[row][1]; // Column 2
        if (Is_Button_Pressed(&PINB, COL3_PIN)) return key_map[row][2]; // Column 3
    }
    
    // No key press detected, return null character
    return '\0';
}
