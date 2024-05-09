/*
 * ADC.c
 */

#include "main.h"
#include "ADC.h"

void USER_ADC1_Init( void )
{

  ADC1->CR1	&=	~(ADC_CR1_DUALMOD);	// Step 1 - Select independent mode
  ADC1->CR2	|=	ADC_CR2_CONT;		// Step 2 - Select conversion mode
  ADC1->CR2	&= 	~(ADC_CR2_ALIGN);	//	and format for ADC result
  ADC1->SMPR2	&= 	~(ADC_SMPR2_SMP0);	// Step 3 - Select the sample time for the
						//	ADC channel
  ADC1->SQR1	&= 	~(ADC_SQR1_L);		// Step 4 - Select the sequence and number of
						//	conversions for the ADC regular channels
  ADC1->SQR3	&= 	~(ADC_SQR3_SQ1);	// Step 5 - Select the channel for the first ADC
						//	conversion
  ADC1->CR2	|=	ADC_CR2_ADON;		// Step 6 - Enable the ADC module
  ADC1->CR2	|=	ADC_CR2_CAL;		// Step 7 - Perform a calibration after
						// 	each power-up
  while ( ADC1->CR2 & ADC_CR2_CAL );		// Step 8 - Wait until the bit is reset by
						//	hardware after calibration is complete
  ADC1->CR2	|=	ADC_CR2_ADON;		// Step 9 - Start conversion
}

uint16_t USER_ADC1_Convert( void )
{

  while(!( ADC1->SR & ADC_SR_EOC ));		// Wait for end of conversion
  return ADC1->DR;

}

float scaleVoltageValue( float voltageValue, float min, float max )
{ 

  float normalizedVoltageValue = (voltageValue - min) / (max - min) * 100;
  return normalizedVoltageValue;

}