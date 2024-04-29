/*
 * main.c
 */

/* Libraries, Definitions and Global Declarations */

#include "main.h"
#include "ADC.h"
#include "uart.h"

volatile uint32_t ConversionData;

/* Function prototypes */

void USER_RCC_ClockEnable( void );
void USER_GPIO_Init( void );

int main( void )
{
  /* Loop forever */

  USER_RCC_ClockEnable( );
  USER_GPIO_Init( );
  USER_USART1_Init( );
  USER_ADC_Init();

  for(;;)
  {
      ConversionData = USER_ADC1_Convert();
      printf("%lu\n\r", (unsigned long)ConversionData);
  }
}

void USER_RCC_ClockEnable( void )
{

  // RCC_APB2ENR modified to IO port A clock enable

  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;		// To set IOPAEN bit

  // RCC_APB2ENR modified to enable the clock for USART1

  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;		// To set USART1EN bit

  // RCC_APB2ENR and RCC_CFGR modified to enable and adjust the clock for ADC1

  RCC->APB2ENR	|=	RCC_APB2ENR_ADC1EN;	// Enable clock for ADC1
  RCC->CFGR	|=	RCC_CFGR_ADCPRE;	// Adjust ADC input clock

}

void USER_GPIO_Init( void )
{
  // Pin PA1 as analog input

  GPIOA->CRL	&=	~( GPIO_CRL_MODE1 )
		&	~( GPIO_CRL_CNF1 );

  // Pin PA9 (USART1_TX) as alternate function output push-pull, max speed 10MHz

  GPIOA->CRH	&=	~( 0x1UL <<  6U )
		&	~( 0x2UL <<  4U );

  GPIOA->CRH	|=	 ( 0x2UL <<  6U )
		|	 ( 0x1UL <<  4U );
}
