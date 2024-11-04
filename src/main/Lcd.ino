#include "dio.h"			  /* Include AVR std. library file */
#include <util/delay.h>	  /* Include Delay header file */
#include "LCD.h"

#define LCD_Dir  DDRD			/* Define LCD data port direction */
#define LCD_Port PORTD		/* Define LCD data port */

#define RS_EN_Dir  DDRB		/* Define RS and En data port direction */
#define RS_EN_Port PORTB  /* Define RS and En port */
#define RS PB0				    /* Define Register Select pin */
#define EN PB1 				    /* Define Enable signal pin */



void LCD_Send( unsigned char data,unsigned char mode )
{
  
	LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0); /* sending upper nibble */
  if(mode == MODE_DATA){
    RS_EN_Port |= (1<<RS);
  }else if(mode == MODE_COMMAND){
    RS_EN_Port &= ~ (1<<RS);
  }
			/* RS=1, data reg. */
	RS_EN_Port|= (1<<EN);
	_delay_us(1);
	RS_EN_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (data << 4); /* sending lower nibble */
	RS_EN_Port |= (1<<EN);
	_delay_us(1);
	RS_EN_Port &= ~ (1<<EN);
	_delay_ms(2);
}
void LCD_DecrementCursor(void){
  LCD_Send (0x10,MODE_COMMAND);		/* Move Cursor to the left  */
	_delay_ms(1000);
}
void LCD_Init (void)			/* LCD Initialize function */
{
	LCD_Dir = 0xFF;			    /* Make LCD port direction as o/p */
  	RS_EN_Dir |= (1 << EN) | (1 << RS);

	_delay_ms(20);			    /* LCD Power ON delay always >15ms */
	
	LCD_Send(0x02,MODE_COMMAND);		  /* send for 4 bit initialization of LCD  */
	LCD_Send(0x28,MODE_COMMAND);      /* 2 line, 5*7 matrix in 4-bit mode */
	LCD_Send(0x0c,MODE_COMMAND);      /* Display on cursor off*/
	LCD_Send(0x06,MODE_COMMAND);      /* Increment cursor (shift cursor to right)*/
	LCD_Send(0x01,MODE_COMMAND);      /* Clear display screen*/
	_delay_ms(2);
}

void LCD_String (char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCD_Send (str[i],MODE_DATA);
	}
}

void LCD_String_xy (char row, char pos, char *str)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	  LCD_Send((pos & 0x0F)|0x80,MODE_COMMAND);	                  /* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	  LCD_Send((pos & 0x0F)|0xC0,MODE_COMMAND);	                  /* Command of first row and required position<16 */
    
	LCD_String(str);	                              	/* Call LCD string function */
}

void LCD_Clear()
{
	LCD_Send (0x01,MODE_COMMAND);		/* Clear display */
	_delay_ms(2);
	LCD_Send (0x80,MODE_COMMAND);		/* Cursor at home position */
}