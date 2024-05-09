/*
 * uart.h
 */

#ifndef UART_H_
#define UART_H_

/*	USARTDIV = F_PCLK / (16 X DESIRED BAUD RATE)
 * 	USARTDIV = 64 MHz / (16 X 115200 bps)
 * 	USARTDIV = 34.72222222
 * 	DIV_Mantissa = 0d34 = 0x22
 * 	DIV_Fraction = 16 X 0d0.340277778 = 0d11.55555556 = 0xC
 * 	USARTDIV = 0x22B
*/

// USART peripheral configuration bits and baud rate register value

#define USART_CR1_UE     0x1UL << 13U 		// USART enable bit
#define USART_CR1_M      0x1UL << 12U  		// Word length (8 bits)
#define USART_CR2_STOP   0x3UL << 12U  		// Number of stop bits (1 stop bit)
#define USARTDIV         0x22B			// Baud rate divisor for desired baud rate

// Transmitter bits

#define USART_CR1_TE     0x1UL <<  3U 		// Transmitter enable bit
#define USART_SR_TXE   	 0x1UL <<  7U 		// Transmit data register empty flag

// Function prototypes for USART

void USER_USART1_Init( void ); // Initialize USART1

// Transmit

int _write( int, char*, int );		// Custom _write function to redirect standard output to USART1

#endif /* UART_H_ */

