/*
 * main.c
 */

/* Libraries, Definitions and Global Declarations */

#include "main.h"
#include "uart.h"
#include "matrixkeyboard.h"

char selectedKey;

/* Function prototypes */

void USER_RCC_ClockEnable( void );
void USER_GPIO_Init( void );

int main( void )
{
  /* Loop forever */

  USER_RCC_ClockEnable( );
  USER_GPIO_Init( );
  USER_USART1_Init();

  for(;;)
  {
      selectedKey = USER_MATRIX_KEYBOARD_Read();
      printf("%c", selectedKey);
  }
}

void USER_RCC_ClockEnable( void )
{

  // RCC_APB2ENR modified to IO port A clock enable

  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;		// To set IOPAEN bit

  // RCC_APB2ENR modified to IO port B clock enable

  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;		// To set IOPBEN bit

  // RCC_APB2ENR modified to enable the clock for USART1

  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;		// To set USART1EN bit

}

void USER_GPIO_Init( void )
{
  // Pin PB1 as input pull up

  GPIOB->CRL	&=	~( GPIO_CRL_MODE1 )
		&	~( GPIO_CRL_CNF1_0 );

  GPIOB->CRL	|= 	 ( GPIO_CRL_CNF1_1 );
  GPIOB->ODR	|=	 ( GPIO_ODR1 );

  // Pin PB15 as input pull up

  GPIOB->CRH	&=	~( GPIO_CRH_MODE15 )
		&	~( GPIO_CRH_CNF15_0 );

  GPIOB->CRH	|= 	 ( GPIO_CRH_CNF15_1 );
  GPIOB->ODR	|=	 ( GPIO_ODR15 );

  // Pin PB14 as input pull up

  GPIOB->CRH	&=	~( GPIO_CRH_MODE14 )
		&	~( GPIO_CRH_CNF14_0 );

  GPIOB->CRH	|= 	 ( GPIO_CRH_CNF14_1 );
  GPIOB->ODR	|=	 ( GPIO_ODR14 );

  // Pin PB13 as input pull up

  GPIOB->CRH	&=	~( GPIO_CRH_MODE13 )
		&	~( GPIO_CRH_CNF13_0 );

  GPIOB->CRH	|= 	 ( GPIO_CRH_CNF13_1 );
  GPIOB->ODR	|=	 ( GPIO_ODR13 );

  // Pin PB10 as output

  GPIOB->CRH	&=	~( GPIO_CRH_CNF10 )
		&	~( GPIO_CRH_MODE10_0 );

  GPIOB->CRH 	|=	 ( GPIO_CRH_MODE10_1 );
  GPIOB->ODR 	|=	 ( GPIO_ODR_10 );

  // Pin PB6 as output

  GPIOB->CRL	&=	~( GPIO_CRL_CNF6 )
		&	~( GPIO_CRL_MODE6_0 );

  GPIOB->CRL 	|=	 ( GPIO_CRL_MODE6_1 );
  GPIOB->ODR 	|=	 ( GPIO_ODR6 );

  // Pin PB5 as output

  GPIOB->CRL	&=	~( GPIO_CRL_CNF5 )
		&	~( GPIO_CRL_MODE5_0 );

  GPIOB->CRL 	|=	 ( GPIO_CRL_MODE5_1 );
  GPIOB->ODR 	|=	 ( GPIO_ODR5 );

  // Pin PB7 as output

  GPIOB->CRL	&=	~( GPIO_CRL_CNF7 )
		&	~( GPIO_CRL_MODE7_0 );

  GPIOB->CRL 	|=	 ( GPIO_CRL_MODE7_1 );
  GPIOB->ODR 	|=	 ( GPIO_ODR7 );

  // Pin PA9 (USART1_TX) as alternate function output push-pull, max speed 10MHz

  GPIOA->CRH	&=	~( GPIO_CRH_CNF9_0 )
   		&	~( GPIO_CRH_MODE9 );

  GPIOA->CRH	|=	 ( GPIO_CRH_CNF9 )
   		|	 ( GPIO_CRH_MODE9_0 );
}
