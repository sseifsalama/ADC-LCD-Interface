#include <avr/interrupt.h>
#include "uart.h"

// Set the baud rate for UART communication
void UART_SetBaudRate(uint32_t baud_rate) {
    uint16_t ubrr = F_CPU / ((baud_rate*16) - 1); // Calculate the UBRR value using the baud rate formula
    UBRR0H = (ubrr >> 8);  // Load the high byte of UBRR
    UBRR0L = ubrr;  // Load the low byte of UBRR
}

// Initialize UART with the given baud rate
void UART_Init(uint32_t baud_rate) {
    UART_SetBaudRate(baud_rate);  // Set the baud rate for UART
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);  // Enable UART receiver and transmitter
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);  // Set the data size to 8-bit (UCSZ01, UCSZ00)
    UCSR0B |= (1 << RXCIE0);  // Enable receive interrupt (so that ISR is triggered on receiving data)
}

// Send a single character via UART
void UART_SendChar(unsigned char data) {
    while (!(UCSR0A & ( 1 << UDRE0)));  // Wait for the data register to be empty (ready to send)
    UDR0 = data;  // Send the character through UART
}

// Send a string of characters via UART
void UART_SendString(char* string) {
    int i = 0;
    while(string[i]) { 
        UART_SendChar(string[i++]);  // Send each character of the string
    }
}

// Receive a single character via UART
char UART_Receive() {
    while((UCSR0A & (1 << RXC0)) == 0);  // Wait until data is received (RXC0 bit set)
    return UDR0;  // Return the received character from the data register
}

// Read an integer value (16-bit) via UART
unsigned int UART_ReadInt(void) {
    unsigned int value = 0;
    while ( ! (UCSR0A & ( 1 << RXC0)) );  // Wait for data to be received
    value = UDR0;  // Store the first 8 bits (high byte)
    value <<= 8;  // Shift the value to make room for the low byte
    value |= UDR0;  // Store the next 8 bits (low byte)
    return value;  // Return the 16-bit integer
}

// Receive a string via UART (up to a maximum size)
void UART_ReceiveString(char* buffer, uint16_t bufferSize) {
    uint16_t i = 0;
    char receivedChar;

    while (i < (bufferSize - 1)) {  // Ensure we don't exceed buffer size
        receivedChar = UART_Receive();  // Get the received character

        if (receivedChar == '\n' || receivedChar == '\0') {  // Check for end of string
            break;
        }

        buffer[i++] = receivedChar;  // Store received character in buffer
    }
    buffer[i] = '\0';  // Null-terminate the string
}

// UART RX interrupt service routine (ISR) - Triggered on receiving data
ISR(USART_RX_vect) { 
    char receivedChar = UDR0;  // Read the received character from the data register

    // Store the received character in the buffer if there is space
    if (commandIndex < BUFFER_SIZE - 1) {
        receivedCommand[commandIndex++] = receivedChar;
    }

    // Check if the received character is the end of a command ('\n' or '\0')
    if (receivedChar == '\n' || receivedChar == '\0') {
        receivedCommand[commandIndex - 1] = '\0';  // Null-terminate the string
        rx_flag = 1;  // Set the flag to indicate that a complete command is received
    }
}
