/*
 * ADC.h
 */

#ifndef ADC_H_
#define ADC_H_

#define RCC_APB2ENR_ADC1EN		( 0x1UL << 9U )
#define RCC_CFGR_ADCPRE			( Ox3UL << 14U )
#define ADC_CR1_DUALMOD			( 0x15UL << 16U )
#define ADC_CR2_CONT			( 0x1UL << 1U )
#define ADC_CR2_ALIGN			( 0x1UL << 11U )
#define ADC_SMPR2_SMP0			( 0x7UL << 0U )
#define ADC_SQR1_L				( 0x15UL << 20U )
#define ADC_SQR3_SQ1			( 0x31UL << 0U )
#define ADC_CR2_ADON			( 0x1UL << 0U )

void USER_ADC_Init( void );

#endif /* ADC_H_ */
