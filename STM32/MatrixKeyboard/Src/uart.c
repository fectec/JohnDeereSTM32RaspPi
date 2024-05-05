/*
 * uart.c
 */

#include "main.h"
#include "uart.h"

void USER_USART1_Init( void ) {
	USART1->CR1	|=	 USART_CR1_UE;		//	Step 1 - USART enabled
	USART1->CR1	&=	~USART_CR1_M;		//	Step 2 - 8 Data bits
	USART1->CR2	&=	~USART_CR2_STOP;	//	Step 3 - 1 Stop bit
	USART1->BRR	 =	 USARTDIV;		//	Step 5 - Desired baud rate
	USART1->CR1	|= 	 USART_CR1_TE;		//	Step 6 - Transmitter enabled
}

/* Custom implementation of _write function, called by the C
 * runtime library to perform the writing of any function that
 * writes to the standard output.
 *
 * It redirects standard output stream in C to USART peripheral
 * device */

int _write (int file, char *ptr, int len) {

  int DataIdx;

  for( DataIdx = 0 ; DataIdx < len; DataIdx++ )
  {
	  while(!( USART1->SR & USART_SR_TXE ));	// Wait until USART_DR is empty
	  USART1->DR = *ptr++;				// Transmit data
  }

  return len;
}
