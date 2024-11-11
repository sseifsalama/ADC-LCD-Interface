#include <util/delay.h>
#include <string.h>
#include "Lcd.h"
#include "adc.h"
#include "dio.h"
#include "uart.h"
#include "keypad.h"
#include <stdlib.h>


#define SAMPLE_N0 20


unsigned char buffer[5];  // Increased buffer size for safety
unsigned int channel;

unsigned char samples[SAMPLE_N0];
uint8_t sample_index = 0;

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
  LCD_String_xy(1, 4,"    ");
  LCD_String_xy(1, 4, sllm);

  LCD_String_xy(1, 8, "HHM:");
  LCD_String_xy(1, 12,"    ");
  LCD_String_xy(1, 12, shhm);
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

      if(channel == 0){
        samples[sample_index] = adc_reading;
        sample_index++;
        if(sample_index > SAMPLE_N0 - 1) sample_index = 0;
        unsigned short avg_ldr = 0;
        for(uint8_t i = 0; i < SAMPLE_N0 - 1; i++){
          avg_ldr += samples[i];
        }
        avg_ldr /= 20;
        adc_reading = avg_ldr;
      }
      // Display sensor reading
      itoa(adc_reading, buffer, 10);
      LCD_String_xy(0, 4, buffer);
      UART_SendString(buffer);
      UART_SendString("\n");
     //UART_SendChar('\n');
     //_delay_ms(400);
       if (key == '4'){

        if(llm - 5 > 0){
          llm = llm - 5;
        }else{
          llm = 0;
        }
         _delay_ms(50);

     } else if(key == '5'){

        if(llm + 5 < hhm ){
          llm = llm + 5;
          
        }
        _delay_ms(50);

     } else if (key == '7'){

        if(hhm - 5 > llm){
          hhm = hhm - 5;
        }
        _delay_ms(50);

     } else if(key == '8'){

        if(hhm + 5 < 1025){
          hhm = hhm + 5;
        }else{
          hhm = 1025;
        }
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
      _delay_ms(1);
      LCD_String_xy(0, 4,"    ");
    
    }
    LCD_Clear();
    key = '\0';  // Reset key for the next iteration
  }
  return 0;
}