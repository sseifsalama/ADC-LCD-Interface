// Include Guard to avoid multiple inclusion
#ifndef _uart_
#define _uart_

// Define buffer size for storing received commands
#define BUFFER_SIZE 16

// UART Control and Status Registers
#define UCSR0A  (*(volatile unsigned char*)0xC0) // UART Control/Status Register A

// Bits for UCSR0A register
#define UDRE0 5 // Data register empty flag (set when the data register is empty)
#define RXC0 7 // Receive complete flag (set when data is received)

#define UCSR0B  (*(volatile unsigned char*)0xC1) // UART Control/Status Register B

// Bits for UCSR0B register
#define RXEN0 4 // Enable receiver (set to enable UART receiver)
#define TXEN0 3 // Enable transmitter (set to enable UART transmitter)
#define RXCIE0 7 // Enable receive interrupt (set to enable interrupt on receiving data)

#define UCSR0C  (*(volatile unsigned char*)0xC2) // UART Control/Status Register C

// Bits for configuring data size
#define UCSZ00 1 // Character size bit 0 (part of UCSZ00 and UCSZ01 to set data size)
#define UCSZ01 2 // Character size bit 1 (part of UCSZ00 and UCSZ01 to set data size)

#define UBRR0L  (*(volatile unsigned char*)0xC4) // Baud rate register (low byte)
#define UBRR0H  (*(volatile unsigned char*)0xC5) // Baud rate register (high byte)
#define UDR0  (*(volatile unsigned char*)0xC6) // UART Data Register (for sending/receiving data)

volatile char receivedCommand[BUFFER_SIZE];  // Buffer for storing received commands
volatile uint8_t commandIndex = 0;  // Index for the current position in the command buffer
volatile int rx_flag = 0;  // Flag to indicate that a complete command has been received

// Function Declarations

// Set the baud rate for UART communication (calculates the baud rate based on the given value)
void UART_SetBaudRate(uint32_t baud_rate);

// Initialize UART with the given baud rate
void UART_Init(uint32_t baud_rate);

// Send a single character over UART
void UART_SendChar(unsigned char data);

// Send a string over UART
void UART_SendString(char* string);

// Receive a single character from UART
char UART_Receive();

// Receive a string from UART and store it in the provided buffer
void UART_ReceiveString(char* buffer, uint16_t bufferSize);

// Read an integer from UART (useful for receiving numbers)
unsigned int UART_ReadInt(void);

#endif
