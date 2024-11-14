#include "dio.h"
#include "Lcd.h"
#include <util/delay.h>

// LCD function for sending command or data
void LCD_Send(unsigned char data, uint8_t mode) {
    
    // Send the upper nibble (first half of the 8 bits) to LCD
    LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0); 
    
    // Set RS pin based on mode: HIGH for data, LOW for command
    if (mode == MODE_DATA) {
        Set_PIN_State(&RS_EN_Port, RS, HIGH); // Data mode
    } else if (mode == MODE_COMMAND) {
        Set_PIN_State(&RS_EN_Port, RS, LOW); // Command mode
    }

    // Enable pulse to latch data
    Set_PIN_State(&RS_EN_Port, EN, HIGH);
    _delay_us(1); 
    Set_PIN_State(&RS_EN_Port, EN, LOW);
    _delay_us(200); // Delay for LCD processing

    // Send the lower nibble (second half of the 8 bits) to LCD
    LCD_Port = (LCD_Port & 0x0F) | (data << 4);
    Set_PIN_State(&RS_EN_Port, EN, HIGH);
    _delay_us(1); 
    Set_PIN_State(&RS_EN_Port, EN, LOW);
    _delay_ms(2); // Wait for data to process
}

// LCD Initialization function
void LCD_Init (void) {
    _delay_ms(20); // Delay for LCD power-up

    LCD_Send(RETURN_CURSOR_HOME, MODE_COMMAND); // Reset cursor
    LCD_Send(LCD_4BIT_2LN, MODE_COMMAND); // 4-bit mode, 2 lines
    LCD_Send(DISPLAY_ON_CURSOR_OFF, MODE_COMMAND); // Display on, cursor off
    LCD_Send(LCD_ENTRY_RIGHT, MODE_COMMAND); // Move cursor to the right
    LCD_Send(CLEAR_DISPLAY, MODE_COMMAND); // Clear the display

    _delay_ms(2); // Wait after clear
}

// LCD function for printing string on the screen
void LCD_String (char *str) {
    int i;
    // Loop through the string and send each character
    for(i = 0; str[i] != 0; i++) {
        LCD_Send(str[i], MODE_DATA); // Send character in data mode
    }
}

// LCD function for printing string on a specific position
void LCD_String_xy (uint8_t row, uint8_t pos, char *str) {
    // Set cursor to specific position
    if (row == 0 && pos < 16)
        LCD_Send((pos & 0x0F) | SET_CURSOR_LINE1, MODE_COMMAND); // Row 1
    else if (row == 1 && pos < 16)
        LCD_Send((pos & 0x0F) | SET_CURSOR_LINE2, MODE_COMMAND); // Row 2
    
    LCD_String(str); // Print string at specified location
}

// LCD function for clearing the screen
void LCD_Clear() {
    LCD_Send(CLEAR_DISPLAY, MODE_COMMAND); // Send clear command
    _delay_ms(2); // Delay after clearing
    LCD_Send(SET_CURSOR_LINE1, MODE_COMMAND); // Reset cursor position
}
