/*
 * ADC.c
 */

#include "main.h"
#include "ADC.h"

void USER_ADC_Init( void ) {
	RCC->APB2ENR	|=	RCC_APB2ENR_ADC1EN;		// Step 1 - Enable clock for ADC1
	RCC->CFGR		|=	RCC_CFGR_ADCPRE;		// Step 2 - Adjust ADC input clock
	ADC1->CR1		&=	~(ADC_CR1_DUALMOD);		// Step 3 - Select independent mode
	ADC1->CR2		|=	ADC_CR2_CONT;			// Step 4 - Select conversion mode
	ADC1->CR2		&= ~(ADC_CR2_ALIGN);		//			and format for ADC result
	ADC1->SMPR2		&= ~(ADC_SMPR2_SMP0);		// Step 5 - Select the sample time for the
												//			ADC channel
	ADC1->SQR1		&= ~(ADC_SQR1_L);			// Step 6 - Select the sequence and number of
												//			conversions for the ADC regular channels
	ADC1->SQR3		&= ~(ADC_SQR3_SQ1);			// Step 7 - Select the channel for the first ADC
												//			conversion
	ADC1->CR2		|=	ADC_CR2_ADON;
}
