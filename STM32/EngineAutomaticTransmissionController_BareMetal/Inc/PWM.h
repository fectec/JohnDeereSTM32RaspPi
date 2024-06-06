/*
 * PWM.h
 */

#ifndef PWM_H_
#define PWM_H_

// PWM prescaler, period and duty cycle register values

#define PWM_PSC_20MS		19
#define PWM_ARR_20MS		63999

#define PWM_CCRX_2_5		1600
#define PWM_CCRX_7_5		4800
#define PWM_CCRX_12_5		8000

// Function prototype for PWM

void USER_PWM_Init( void );
void USER_PWM_Generate( uint16_t, uint16_t, uint16_t );

#endif /* PWM_H_ */
