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
  USER_ADC_Init();

  for(;;)
  {
      ConversionData = USER_ADC1_Convert();
      printf("%lu\n", (unsigned long)ConversionData);
  }
}

void USER_RCC_ClockEnable( void )
{

  RCC->APB2ENR	|=	RCC_APB2ENR_IOPAEN;	// I/O port A clock enable
  RCC->APB2ENR	|=	RCC_APB2ENR_ADC1EN;	// Enable clock for ADC1
  RCC->CFGR	|=	RCC_CFGR_ADCPRE;	// Adjust ADC input clock

}

void USER_GPIO_Init( void )
{
  // Pin PA1 as analog input

  GPIOA->CRL	&=	~( GPIO_CRL_MODE1 )
		&	~( GPIO_CRL_CNF1 );
}
