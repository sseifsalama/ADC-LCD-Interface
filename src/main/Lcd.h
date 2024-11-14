// Include Guard to avoid multiple inclusion
#ifndef __Lcd__
#define __Lcd__ 

// LCD Modes: Data Mode sends character data; Command Mode sends instructions
#define MODE_DATA 1 // Data mode to display characters
#define MODE_COMMAND 0 // Command mode to send instructions

// LCD Commands: Basic Commands for control
#define CLEAR_DISPLAY 0x01 // Clear the display
#define RETURN_CURSOR_HOME 0x02 // Reset cursor to starting position

// LCD Commands: Entry Mode settings (controls cursor and text direction)
#define LCD_ENTRY_LEFT 0x04 // Text goes left
#define LCD_ENTRY_LEFT_DISPLAY_RIGHT 0x05 // Text goes left, display shifts right
#define LCD_ENTRY_RIGHT 0x06 // Text goes right
#define LCD_ENTRY_RIGHT_DISPLAY_LEFT 0x07 // Text goes right, display shifts left

// LCD Commands: Display and Cursor Modes
#define DISPLAY_OFF_CURSOR_OFF 0x08 // Turn off display and cursor
#define DISPLAY_ON_CURSOR_OFF 0x0C // Display on, cursor off
#define DISPLAY_ON_CURSOR_ON 0x0E // Display on with cursor visible
#define DISPLAY_ON_CURSOR_BLINK 0x0F // Display on with blinking cursor

// LCD Commands: Cursor and Display Shifts (manually move cursor or text)
#define CURSOR_SHIFT_LEFT 0x10 // Move cursor left
#define CURSOR_SHIFT_RIGHT 0x14 // Move cursor right
#define DISPLAY_SHIFT_LEFT 0x18 // Shift entire display left
#define DISPLAY_SHIFT_RIGHT 0x1C // Shift entire display right

// LCD Commands: Set Cursor Position (Line 1 or Line 2)
#define SET_CURSOR_LINE1 0x80 // Start position on first line
#define SET_CURSOR_LINE2 0xC0 // Start position on second line

// LCD Commands: Configure Interface Mode (4-bit or 8-bit, 1 or 2 lines)
#define LCD_
