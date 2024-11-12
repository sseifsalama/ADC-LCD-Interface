#include <util/delay.h>
#include <string.h>
#include "Lcd.h"
#include "adc.h"
#include "dio.h"
#include "uart.h"
#include "keypad.h"
#include <stdlib.h>


#define SAMPLE_N0 30


unsigned char buffer[5];  // Increased buffer size for safety

uint8_t channel; // Variable for choosing a channel

unsigned char samples[SAMPLE_N0]; // Array to store LDR values
uint8_t sample_index = 0; // Index of Samples Array


// Function used to Display the limits on the LCD

void display_limits(int llm, int hhm) {

  char sllm[6];
  char shhm[6];
  
  itoa(llm, sllm, 10); // Converting
  itoa(hhm, shhm, 10);

  LCD_String_xy(1, 0, "LLM:");
  LCD_String_xy(1, 4,"    ");
  LCD_String_xy(1, 4, sllm);

  LCD_String_xy(1, 8, "HHM:");
  LCD_String_xy(1, 12,"    ");
  LCD_String_xy(1, 12, shhm);

}

void init() {

  dio_init();
  LCD_Init();
  UART_Init(9600);
  Adc_Init();

}

int main(void) {

  init();
  int llm = 200;
  int hhm = 500;

  while (1) {

    UART_SendString("System Started\n");
    LCD_Send(DISPLAY_ON_CURSOR_OFF, MODE_COMMAND);
    LCD_String("Analog Sensors");
    LCD_Send(SET_CURSOR_LINE2, MODE_COMMAND);
    LCD_String("1:POT  2:LDR"); 

    while (key != '1' && key != '2') { // Wait for a key to get pressed
      key = keypad_get_key();
    }

    LCD_Clear(); // Clear Screen

    if (key == '1') {

      channel = POT_PIN;
      LCD_String("POT:");
      UART_SendString("Potentiometer Chosen\n");

    } else if (key == '2') {

      channel = LDR_PIN;
      LCD_String("LDR:");
      UART_SendString("Light Dependent Resistor Chosen\n");

    } 
    
    while (key != '9') {
      
      adc_reading = Adc_ReadChannel(channel);

      if(channel == LDR_PIN){

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

      // Display sensor reading and Send through UART

      itoa(adc_reading, buffer, 10);
      LCD_String_xy(0, 4, buffer);
   
       if (key == '4'){

        if(llm - 5 > 0){
          llm = llm - 5;
          UART_SendString("Low Limit Decreased\n");
        }else{
          llm = 0;
          UART_SendString("Low Limit cannot be Decreased\n");
        }
         _delay_ms(50);

     } else if(key == '5'){

        if(llm + 5 < hhm ){
          llm = llm +  5;
          UART_SendString("Low Limit Increased\n");
        }else{
          UART_SendString("Low Limit cannot be more than High Limit\n");
        }
        _delay_ms(50);

     } else if (key == '7'){

        if(hhm - 5 > llm){
          hhm = hhm - 5;
          UART_SendString("High Limit Decreased\n");
        }else{
          UART_SendString("High Limit cannot be less than Low Limit\n");
        }

        _delay_ms(50);

     } else if(key == '8'){
        
        if(hhm + 5 < 1025){
          hhm = hhm + 5;
          UART_SendString("High Limit Increased\n");
        }else{
          hhm = 1025;
          UART_SendString("High Limit cannot be Increased\n");
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


