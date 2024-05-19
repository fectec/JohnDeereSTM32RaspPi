/*
 * uart.c
 */

#include "libraries.h"
#include "uart.h"
#include "main.h"
#include "GPIO.h"

// Initialize USART

void USER_USART_Init( uint8_t USART )
{
  if( USART == 0 )
  {
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; 		// Clock enable for USART1
    USER_GPIO_Define(PORTA, 9, OUT_10, OUT_AF_PP);	// Pin PA9 (USART1_TX) as alternate function output push-pull, max speed 10 MHz

    USART1->CR1	|=	 USART_CR1_UE;			// Step 1 - USART enabled
    USART1->CR1	&=	~USART_CR1_M;			// Step 2 - 8 Data bits
    USART1->CR2	&=	~USART_CR2_STOP;		// Step 3 - 1 Stop bit
    USART1->BRR	 =	 USARTDIV;			// Step 5 - Desired baud rate
    USART1->CR1	|= 	 USART_CR1_TE;			// Step 6 - Transmitter enabled
  }
  else if( USART == 1 )
  {
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN; 		// Clock enable for USART2
    USER_GPIO_Define(PORTA, 2, OUT_10, OUT_AF_PP);	// Pin PA2 (USART2_TX) as alternate function output push-pull, max speed 10 MHz

    USART2->CR1	|=	 USART_CR1_UE;
    USART2->CR1	&=	~USART_CR1_M;
    USART2->CR2	&=	~USART_CR2_STOP;
    USART2->BRR	 =	 USARTDIV;
    USART2->CR1	|= 	 USART_CR1_TE;
  }
  else if( USART == 2 )
  {
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN; 		// Clock enable for USART3
    USER_GPIO_Define(PORTA, 2, OUT_10, OUT_AF_PP);	// Pin PB10 (USART3_TX) as alternate function output push-pull, max speed 10 MHz

    USART3->CR1	|=	 USART_CR1_UE;
    USART3->CR1	&=	~USART_CR1_M;
    USART3->CR2	&=	~USART_CR2_STOP;
    USART3->BRR	 =	 USARTDIV;
    USART3->CR1	|= 	 USART_CR1_TE;
  }
}

/* Custom implementation of _write function, called by the C
 * runtime library to perform the writing of any function that
 * writes to the standard output.
 *
 * It redirects standard output stream in C to USART peripheral
 * device */

int _write( int file, char *ptr, int len )
{
  int DataIdx;

  for( DataIdx = 0 ; DataIdx < len; DataIdx++ )
  {
    while(!( USART1->SR & USART_SR_TXE ));		// Wait until USART_DR is empty
    USART1->DR = *ptr++;				// Transmit data
  }

  return len;
}
