// Include Guard to avoid multiple inclusion
#ifndef __Lcd__
#define __Lcd__ 

#define MODE_DATA 1
#define MODE_COMMAND 0

void LCD_Send (unsigned char char_data,unsigned char mode);
void LCD_Init (void);
void LCD_String (char *str);
void LCD_String_xy (char row, char pos, char *str);
void LCD_Clear();
void LCD_DecrementCursor(void);
#endif