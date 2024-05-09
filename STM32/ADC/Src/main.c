/*
 * main.c
 */

/* Libraries, Definitions and Global Declarations */

#include "main.h"
#include "ADC.h"
#include "uart.h"

volatile uint16_t ConversionData;
volatile float Voltage;

/* Function prototypes */

void USER_RCC_ClockEnable( void );
void USER_GPIO_Init( void );

int main( void )
{
  /* Loop forever */

  USER_RCC_ClockEnable( );
  USER_GPIO_Init( );
  USER_USART1_Init( );
  USER_ADC1_Init();

  for(;;)
  {
      ConversionData = USER_ADC1_Convert();
      Voltage = 0.00080586 * ConversionData;

      printf("Voltage: %f\n\r", Voltage);
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

  GPIOA->CRL	&=	~( GPIO_CRL_MODE0 )
		&	~( GPIO_CRL_CNF0 );

  // Pin PA9 (USART1_TX) as alternate function output push-pull, max speed 10MHz

  GPIOA->CRH	&=	~( GPIO_CRH_CNF9_0 )
  		&	~( GPIO_CRH_MODE9 );

  GPIOA->CRH	|=	 ( GPIO_CRH_CNF9 )
  		|	 ( GPIO_CRH_MODE9_0 );
}
