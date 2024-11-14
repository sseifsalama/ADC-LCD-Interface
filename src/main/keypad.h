// Include Guard to avoid multiple inclusion
#ifndef __keypad__
#define __keypad__

// 2D array to map keypad buttons to characters
const char key_map[3][3] = {
    {'1', '2', '3'}, // First row
    {'4', '5', '6'}, // Second row
    {'7', '8', '9'}  // Third row
};

// Variable to store the last pressed key
char key = '\0';

// Function to get the key pressed on the keypad
char keypad_get_key(void);

#endif
