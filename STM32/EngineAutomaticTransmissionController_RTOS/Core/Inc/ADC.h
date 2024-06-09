/*
 * ADC.h
 */

#ifndef ADC_H_
#define ADC_H_

// ADC selection

#define ADC_1			0

// Function prototypes for ADC

void USER_ADC_Init( uint8_t );
uint16_t USER_ADC_Convert( uint8_t );
float scaleVoltageValue( float, float, float );

#endif /* ADC_H_ */
