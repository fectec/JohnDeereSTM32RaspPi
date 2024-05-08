/*
 * main.c
 */

/* Libraries, Definitions and Global Declarations */

#include "main.h"
#include "timer.h"
#include "ADC.h"
#include "uart.h"
#include "matrixkeyboard.h"

// ADC1

volatile uint16_t conversionData;
volatile float voltageValue, normalizedVoltageValue;

// Matrix Keyboard

char selectedKey;
float keyBrakeTorque;

/* Function prototypes */

void USER_RCC_ClockEnable( void );
void USER_GPIO_Init( void );

int main( void )
{

  /* Loop forever */

  USER_RCC_ClockEnable();
  USER_GPIO_Init();
  USER_TIM2_Init( );
  USER_USART1_Init();
  USER_ADC1_Init();

  EngTrModel_initialize();

  for(;;)
  {
    // ADC1

    conversionData = USER_ADC1_Convert();
    voltageValue = 0.00080586 * conversionData;
    normalizedVoltageValue = scaleVoltageValue(voltageValue, 0, 100);

    // Matrix Keyboard

    selectedKey = USER_MATRIX_KEYBOARD_Read();

    if(selectedKey == '5')
    {
      keyBrakeTorque = 100.0;
    }
    else
    {
      keyBrakeTorque = 0.0;
    }

    // Update the values for the Throttle and Brake commands

    USER_TIM2_Delay();

    EngTrModel_U.Throttle = normalizedVoltageValue;
    EngTrModel_U.BrakeTorque = keyBrakeTorque;

    // Update the values into the vehicle model

    EngTrModel_step();

    // Send the output values

    printf("%f,%f,%f", EngTrModel_Y.VehicleSpeed, EngTrModel_Y.EngineSpeed, EngTrModel_Y.Gear);

    USER_TIM2_Delay();        //  1 s
  }

}

void USER_RCC_ClockEnable( void )
{

  // RCC_APB2ENR modified to IO port A clock enable

  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;		// To set IOPAEN bit

  // RCC_APB2ENR modified to IO port B clock enable

  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;		// To set IOPBEN bit

  // RCC_APB1ENR modified to enable the clock for TIM2

  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;		// To set TIM2EN bit

  // RCC_APB2ENR and RCC_CFGR modified to enable and adjust the clock for ADC1

  RCC->APB2ENR	|=	RCC_APB2ENR_ADC1EN;	// Enable clock for ADC1
  RCC->CFGR	|=	RCC_CFGR_ADCPRE;	// Adjust ADC input clock

  // RCC_APB2ENR modified to enable the clock for USART1

  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;		// To set USART1EN bit

}

void USER_GPIO_Init( void )
{

  // Pin PA1 (ADC1 Input) as analog input

  GPIOA->CRL	&=	~( GPIO_CRL_MODE0 )
		&	~( GPIO_CRL_CNF0 );
		
  // Pin PA9 (USART1_TX) as alternate function output push-pull, max speed 10MHz

  GPIOA->CRH	&=	~( GPIO_CRH_CNF9_0 )
   		&	~( GPIO_CRH_MODE9 );

  GPIOA->CRH	|=	 ( GPIO_CRH_CNF9 )
   		|	 ( GPIO_CRH_MODE9_0 );	
   		
  // Pin PB10 (Row 1) as output

  GPIOB->CRH	&=	~( GPIO_CRH_CNF10 )
		&	~( GPIO_CRH_MODE10_0 );

  GPIOB->CRH 	|=	 ( GPIO_CRH_MODE10_1 );
  GPIOB->ODR 	|=	 ( GPIO_ODR_10 );

  // Pin PB6 (Row 2) as output

  GPIOB->CRL	&=	~( GPIO_CRL_CNF6 )
		&	~( GPIO_CRL_MODE6_0 );

  GPIOB->CRL 	|=	 ( GPIO_CRL_MODE6_1 );
  GPIOB->ODR 	|=	 ( GPIO_ODR6 );

  // Pin PB5 (Row 3) as output

  GPIOB->CRL	&=	~( GPIO_CRL_CNF5 )
		&	~( GPIO_CRL_MODE5_0 );

  GPIOB->CRL 	|=	 ( GPIO_CRL_MODE5_1 );
  GPIOB->ODR 	|=	 ( GPIO_ODR5 );

  // Pin PB7 (Row 4) as output

  GPIOB->CRL	&=	~( GPIO_CRL_CNF7 )
		&	~( GPIO_CRL_MODE7_0 );

  GPIOB->CRL 	|=	 ( GPIO_CRL_MODE7_1 );
  GPIOB->ODR 	|=	 ( GPIO_ODR7 );

  // Pin PB1 (Col 1) as input pull up

  GPIOB->CRL	&=	~( GPIO_CRL_MODE1 )
		&	~( GPIO_CRL_CNF1_0 );

  GPIOB->CRL	|= 	 ( GPIO_CRL_CNF1_1 );
  GPIOB->ODR	|=	 ( GPIO_ODR1 );

  // Pin PB15 (Col 2) as input pull up

  GPIOB->CRH	&=	~( GPIO_CRH_MODE15 )
		&	~( GPIO_CRH_CNF15_0 );

  GPIOB->CRH	|= 	 ( GPIO_CRH_CNF15_1 );
  GPIOB->ODR	|=	 ( GPIO_ODR15 );

  // Pin PB14 (Col 3) as input pull up

  GPIOB->CRH	&=	~( GPIO_CRH_MODE14 )
		&	~( GPIO_CRH_CNF14_0 );

  GPIOB->CRH	|= 	 ( GPIO_CRH_CNF14_1 );
  GPIOB->ODR	|=	 ( GPIO_ODR14 );

  // Pin PB13 (Col 4) as input pull up

  GPIOB->CRH	&=	~( GPIO_CRH_MODE13 )
		&	~( GPIO_CRH_CNF13_0 );

  GPIOB->CRH	|= 	 ( GPIO_CRH_CNF13_1 );
  GPIOB->ODR	|=	 ( GPIO_ODR13 );
    		
}
