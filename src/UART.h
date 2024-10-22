// Include Guard to avoid multiple inclusion
#ifndef _uart_
#define _uart_

#define BUFFER_SIZE 16

// Function Declarations
void UART_SetBaudRate(uint32_t baud_rate);
void UART_Init(uint32_t baud_rate);
void UART_SendChar(unsigned char data);
void UART_SendString(char* string);
char UART_Receive();
void UART_ReceiveString(char* buffer, uint16_t bufferSize);
unsigned int UART_ReadInt(void);
#endif