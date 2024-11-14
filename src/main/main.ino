#include <util/delay.h>
#include <string.h>
#include "Lcd.h"
#include "adc.h"
#include "dio.h"
#include "uart.h"
#include "keypad.h"
#include <stdlib.h>

#define SAMPLE_N0 30  // Define number of samples for LDR sensor readings

unsigned char buffer[5];  // Buffer to hold values for display
uint8_t channel;  // Variable for selecting the ADC channel
unsigned char samples[SAMPLE_N0];  // Array to store LDR sensor samples
uint8_t sample_index = 0;  // Index to track current sample in the LDR array

// Function to display the low and high limits on the LCD screen
void display_limits(int llm, int hhm) {
  char sllm[6];  // String to store the low limit value
  char shhm[6];  // String to store the high limit value
  
  itoa(llm, sllm, 10); // Convert low limit to string
  itoa(hhm, shhm, 10); // Convert high limit to string

  // Display low limit and high limit values on LCD
  LCD_String_xy(1, 0, "LLM:");
  LCD_String_xy(1, 4,"    ");
  LCD_String_xy(1, 4, sllm);
  
  LCD_String_xy(1, 8, "HHM:");
  LCD_String_xy(1, 12,"    ");
  LCD_String_xy(1, 12, shhm);
}

// Initialization function for peripherals
void init() {
  dio_init();  // Initialize GPIO
  LCD_Init();  // Initialize LCD
  UART_Init(9600);  // Initialize UART with 9600 baud rate
  Adc_Init();  // Initialize ADC for sensor readings
}

int main(void) {
  init();  // Initialize peripherals

  int llm = 200;  // Initial low limit
  int hhm = 500;  // Initial high limit

  while (1) {
    UART_SendString("System Started\n");  // Send startup message via UART
    LCD_Send(DISPLAY_ON_CURSOR_OFF, MODE_COMMAND);  // Disable cursor on LCD
    LCD_String("Analog Sensors");  // Display sensor menu
    LCD_Send(SET_CURSOR_LINE2, MODE_COMMAND);  
    LCD_String("1:POT  2:LDR");  // Display option to choose sensor

    // Wait for user input to choose sensor
    while (key != '1' && key != '2') { 
      key = keypad_get_key();  // Wait for key press
    }

    LCD_Clear();  // Clear LCD screen

    if (key == '1') {
      channel = POT_PIN;  // Choose potentiometer
      LCD_String("POT:");  // Display 'POT' on LCD
      UART_SendString("Potentiometer Chosen\n");  // Send message via UART

    } else if (key == '2') {
      channel = LDR_PIN;  // Choose LDR
      LCD_String("LDR:");  // Display 'LDR' on LCD
      UART_SendString("Light Dependent Resistor Chosen\n");  // Send message via UART
    }

    // Main loop to handle ADC reading and limit checks
    while (key != '9') {
      
      adc_reading = Adc_ReadChannel(channel);  // Read ADC value from chosen channel

      if (channel == LDR_PIN) {
        samples[sample_index] = adc_reading;  // Store LDR reading
        sample_index++;
        if (sample_index > SAMPLE_N0 - 1) sample_index = 0;  // Loop back to first sample if needed

        unsigned short avg_ldr = 0;
        for (uint8_t i = 0; i < SAMPLE_N0 - 1; i++) {
          avg_ldr += samples[i];  // Calculate average LDR reading
        }
        avg_ldr /= 20;  // Calculate average of 20 readings
        adc_reading = avg_ldr;  // Use the average LDR reading
      }

      // Display ADC reading on LCD and send it via UART
      itoa(adc_reading, buffer, 10);  // Convert ADC value to string
      LCD_String_xy(0, 4, buffer);  // Display on LCD

      // Handle key presses to adjust limits
      if (key == '4') {
        if (llm - 5 > 0) {
          llm = llm - 5;  // Decrease low limit
          UART_SendString("Low Limit Decreased\n");
        } else {
          llm = 0;
          UART_SendString("Low Limit cannot be Decreased\n");
        }
        _delay_ms(50);

      } else if (key == '5') {
        if (llm + 5 < hhm) {
          llm = llm + 5;  // Increase low limit
          UART_SendString("Low Limit Increased\n");
        } else {
          UART_SendString("Low Limit cannot be more than High Limit\n");
        }
        _delay_ms(50);

      } else if (key == '7') {
        if (hhm - 5 > llm) {
          hhm = hhm - 5;  // Decrease high limit
          UART_SendString("High Limit Decreased\n");
        } else {
          UART_SendString("High Limit cannot be less than Low Limit\n");
        }
        _delay_ms(50);

      } else if (key == '8') {
        if (hhm + 5 < 1025) {
          hhm = hhm + 5;  // Increase high limit
          UART_SendString("High Limit Increased\n");
        } else {
          hhm = 1025;
          UART_SendString("High Limit cannot be Increased\n");
        }
        _delay_ms(50);
      }

      // Display the limits on LCD
      display_limits(llm, hhm);

      // Check ADC reading and compare with limits
      if (adc_reading > llm && adc_reading < hhm) {
        LCD_String_xy(0, 13, " OK");  // Display 'OK' if within limits
        Set_PIN_State(&PORTC, PC3, LOW);  // Set PC3 low if within limits
      } else {
        LCD_String_xy(0, 13, "NOK");  // Display 'NOK' if outside limits
        Set_PIN_State(&PORTC, PC3, HIGH);  // Set PC3 high if outside limits
      }

      // Wait for a key press and refresh display
      key = keypad_get_key();
      _delay_ms(1);
      LCD_String_xy(0, 4, "    ");  // Clear ADC value from LCD

    }

    LCD_Clear();  // Clear screen when key '9' is pressed
    key = '\0';  // Reset key for next iteration

  }

  return 0;  // End of program
}


