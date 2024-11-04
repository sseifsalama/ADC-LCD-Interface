#include <util/delay.h>
#include <string.h>
#include "Lcd.h"
#include "adc.h"
#include "dio.h"
#include "uart.h"
#include <stdlib.h>
//Maximum buffer size for commands sent to UART
#define MAX_SIZE 100


 unsigned short adc_reading;
volatile char receivedCommand[BUFFER_SIZE];  // Shared buffer for received commands
volatile uint8_t commandIndex = 0;  // Index for command buffer
volatile int rx_flag = 0;  // Flag indicating a command has been received
unsigned char buffer[4];
//Initialization Function
void init() {
    LCD_Init();
    UART_Init(9600);
    Adc_Init();
}

int main(void) {
  init();
 UART_SendString("asmdsadas");
 
 LCD_Send(0x0E,MODE_COMMAND);
 while (1) {
   LCD_String("Pot:");
   LCD_String_xy(1,0,"LLM:200");
   LCD_String_xy(0,4,buffer);
   LCD_String_xy(1,9,"HHM:500");
   
   adc_reading = Adc_ReadChannel(0);
   itoa(adc_reading, buffer, 10);
   if(adc_reading > 200 && adc_reading < 500){
    LCD_String_xy(0,13,"OK");
   }else{
    LCD_String_xy(0,13,"NOK");
   }
   UART_SendString(buffer);
   UART_SendChar('\n');
   LCD_String_xy(0,4,buffer);

   
   _delay_ms(300);
   
   LCD_Clear();
   
   
 } /* End event loop */
 return (0);
}

