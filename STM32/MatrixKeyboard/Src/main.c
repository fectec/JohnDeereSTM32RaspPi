/*
 * main.c
 */

/* Libraries, Definitions and Global Declarations */

#include "main.h"
#include "matrixkeyboard.h"

/* Function prototypes */

void USER_RCC_ClockEnable( void );
void USER_GPIO_Init( void );

int main( void )
{
  /* Loop forever */

  USER_RCC_ClockEnable( );
  USER_GPIO_Init( );

  for(;;)
  {

  }
}

void USER_RCC_ClockEnable( void )
{

  // RCC_APB2ENR modified to IO port B clock enable

  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;		// To set IOPBEN bit

  // RCC_APB2ENR modified to enable the clock for USART1

  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;		// To set USART1EN bit

}

void USER_GPIO_Init( void )
{

}

