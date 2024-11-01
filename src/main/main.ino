#include <util/delay.h>
#include <string.h>
#include "Lcd.h"
#include "adc.h"
#include "dio.h"
#include "uart.h"

//Maximum buffer size for commands sent to UART
#define MAX_SIZE 100


volatile char receivedCommand[BUFFER_SIZE];  // Shared buffer for received commands
volatile uint8_t commandIndex = 0;  // Index for command buffer
volatile int rx_flag = 0;  // Flag indicating a command has been received

//Initialization Function
void init() {
    LCD_Init();
    UART_Init(9600);
}

int main(void) {
  init();		/* Initialize LCD */
  UART_SendString("Hello");
	LCD_String("Go to Hell");	/* write string on 1st line of LCD*/
	LCD_Send(0xC0,MODE_COMMAND);		            /* Go to 2nd line*/
	LCD_String("DIEEEE!!!");	        /* Write string on 2nd line*/
    while(1);
	return 0;
}

