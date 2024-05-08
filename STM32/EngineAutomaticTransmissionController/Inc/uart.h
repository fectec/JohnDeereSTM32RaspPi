/*
 * uart.h
 */

#ifndef UART_H_
#define UART_H_

/*	USARTDIV = F_PCLK / (16 X DESIRED BAUD RATE)
 * 	USARTDIV = 8 MHz /	(16 X 115200 bps)
 * 	USARTDIV = 4.340277778
 * 	DIV_Mantissa = 0d4 = 0x4
 * 	DIV_Fraction = 16 X 0d0.340277778 = 0d5.444444444 = 0x5
 * 	USARTDIV = 0x45
*/

// USART peripheral configuration bits and baud rate register value

#define USART_CR1_UE     0x1UL << 13U 		// USART enable bit
#define USART_CR1_M      0x1UL << 12U  		// Word length (8 bits)
#define USART_CR2_STOP   0x3UL << 12U  		// Number of stop bits (1 stop bit)
#define USARTDIV         0x45			// Baud rate divisor for desired baud rate

// Transmitter bits

#define USART_CR1_TE     0x1UL <<  3U 		// Transmitter enable bit
#define USART_SR_TXE   	 0x1UL <<  7U 		// Transmit data register empty flag

// Function prototypes for USART

void USER_USART1_Init( void ); // Initialize USART1

// Transmit

int _write( int, char*, int );		// Custom _write function to redirect standard output to USART1

#endif /* UART_H_ */

