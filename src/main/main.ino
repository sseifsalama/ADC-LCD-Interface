#include <util/delay.h>
#include <string.h>
#include "Lcd.h"
#include "adc.h"
#include "dio.h"
#include "uart.h"
#include "keypad.h"
#include <stdlib.h>



unsigned char buffer[5];  // Increased buffer size for safety
unsigned int channel;

void init() {
  dio_init();
  LCD_Init();
  UART_Init(9600);
  Adc_Init();
}

void display_limits(int llm, int hhm) {
  char sllm[6];
  char shhm[6];
  
  itoa(llm, sllm, 10);
  itoa(hhm, shhm, 10);

  LCD_String_xy(1, 0, "LLM:");
  LCD_String_xy(1, 4, sllm);

  LCD_String_xy(1, 9, "HHM:");
  LCD_String_xy(1, 13, shhm);
}

int main(void) {
  init();
  int llm = 200;
  int hhm = 500;

  while (1) {
    LCD_Send(0x0E, MODE_COMMAND);
    LCD_String("Analog Sensors");
    LCD_Send(0xC0, MODE_COMMAND);
    LCD_String("1:POT  2:LDR");

    

    while (key == '\0') {
      key = keypad_get_key();
    }
    LCD_Clear();

    

    if (key == '1') {

      channel = 1;
      LCD_String("POT:");

    } else if (key == '2') {

      channel = 0;
      LCD_String("LDR:");

    } 
    
    while (key != '9') {
      
      adc_reading = Adc_ReadChannel(channel);
      // Display sensor reading
      itoa(adc_reading, buffer, 10);
    LCD_String_xy(0, 4, buffer);
      
     UART_SendString(buffer);
     UART_SendString("\n");
     //UART_SendChar('\n');
     //_delay_ms(400);
     if (key == '4'){
      llm = llm - 5;
      _delay_ms(50);
     } else if(key == '5'){
      llm = llm + 5;
      _delay_ms(50);
     } else if (key == '7'){
      hhm = hhm - 5;
      _delay_ms(50);
     } else if(key == '8'){
      hhm = hhm + 5;
      _delay_ms(50);
     }
     
      
      // Display limits
      display_limits(llm, hhm);

      // Check adc_reading range and display status
      if (adc_reading > llm && adc_reading < hhm) {
        LCD_String_xy(0, 13, " OK");
        Set_PIN_State(&PORTC, PC3, LOW);
      } else {
        LCD_String_xy(0, 13, "NOK");
        Set_PIN_State(&PORTC, PC3, HIGH);
      }

      // Send reading over UART
      //UART_SendString(buffer);
      //UART_SendChar('\n');
      // Delay for display refresh and update key
      
      key = keypad_get_key();
      _delay_ms(100);
      LCD_String_xy(0, 4,"    ");
    
    }
    LCD_Clear();
    key = '\0';  // Reset key for the next iteration
  }
  return 0;
}