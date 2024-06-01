/*
 * ADC.c
 */

#include "libraries.h"
#include "ADC.h"
#include "main.h"
#include "GPIO.h"

// Initialize ADC

void USER_ADC_Init( uint8_t ADC )
{
  RCC->CFGR	|=	RCC_CFGR_ADCPRE;       		// Adjust ADC input clock
  USER_GPIO_Define(PORTA, 0, INP, INP_AN);		// Pin PA0 as analog input

  if( ADC == 0 )
  {
    RCC->APB2ENR	|=	RCC_APB2ENR_ADC1EN;	// ADC1 clock enable

    ADC1->CR1		&=	~(ADC_CR1_DUALMOD);	// Step 1 - Select independent mode
    ADC1->CR2		|=	ADC_CR2_CONT;		// Step 2 - Select conversion mode
    ADC1->CR2		&= 	~(ADC_CR2_ALIGN);	//	and format for ADC result
    ADC1->SMPR2		&= 	~(ADC_SMPR2_SMP0);	// Step 3 - Select the sample time for the
							//	ADC channel
    ADC1->SQR1		&= 	~(ADC_SQR1_L);		// Step 4 - Select the sequence and number of
							//	conversions for the ADC regular channels
    ADC1->SQR3		&= 	~(ADC_SQR3_SQ1);	// Step 5 - Select the channel for the first ADC
							//	conversion
    ADC1->CR2		|=	ADC_CR2_ADON;		// Step 6 - Enable the ADC module
    ADC1->CR2		|=	ADC_CR2_CAL;		// Step 7 - Perform a calibration after
							// 	each power-up
    while ( ADC1->CR2 & ADC_CR2_CAL );			// Step 8 - Wait until the bit is reset by
							//	hardware after calibration is complete
    ADC1->CR2		|=	ADC_CR2_ADON;		// Step 9 - Start conversion
  }
  else if( ADC == 1 )
  {
    RCC->APB2ENR	|=	RCC_APB2ENR_ADC2EN;	// ADC2 clock enable

    ADC2->CR1		&=	~(ADC_CR1_DUALMOD);
    ADC2->CR2		|=	ADC_CR2_CONT;
    ADC2->CR2		&= 	~(ADC_CR2_ALIGN);
    ADC2->SMPR2		&= 	~(ADC_SMPR2_SMP0);

    ADC2->SQR1		&= 	~(ADC_SQR1_L);

    ADC2->SQR3		&= 	~(ADC_SQR3_SQ1);

    ADC2->CR2		|=	ADC_CR2_ADON;
    ADC2->CR2		|=	ADC_CR2_CAL;

    while ( ADC2->CR2 & ADC_CR2_CAL );

    ADC2->CR2		|=	ADC_CR2_ADON;
  }
  else if( ADC == 2 )
  {
    RCC->APB2ENR	|=	RCC_APB2ENR_ADC3EN;	// ADC3 clock enable

    ADC3->CR1		&=	~(ADC_CR1_DUALMOD);
    ADC3->CR2		|=	ADC_CR2_CONT;
    ADC3->CR2		&= 	~(ADC_CR2_ALIGN);
    ADC3->SMPR2		&= 	~(ADC_SMPR2_SMP0);

    ADC3->SQR1		&= 	~(ADC_SQR1_L);

    ADC3->SQR3		&= 	~(ADC_SQR3_SQ1);

    ADC3->CR2		|=	ADC_CR2_ADON;
    ADC3->CR2		|=	ADC_CR2_CAL;

    while ( ADC3->CR2 & ADC_CR2_CAL );

    ADC3->CR2		|=	ADC_CR2_ADON;
  }
}

// Convert Analog value to Digital using ADC

uint16_t USER_ADC_Convert( uint8_t ADC )
{
  if( ADC == 0 )
  {
    while( !( ADC1->SR & ADC_SR_EOC ) );		// Wait for end of conversion
    return ADC1->DR;
  }
  else if( ADC == 1 )
  {
    while( !( ADC2->SR & ADC_SR_EOC ) );
    return ADC2->DR;
  }
  else if( ADC == 2 )
  {
    while( !( ADC3->SR & ADC_SR_EOC ) );
    return ADC3->DR;
  }

  return 0;
}

// Scale ADC read voltage value to a range of 0 to 100

float scaleVoltageValue( float voltageValue, float min, float max )
{ 
  float normalizedVoltageValue = (voltageValue - min) / (max - min) * 100;
  return normalizedVoltageValue;
}
