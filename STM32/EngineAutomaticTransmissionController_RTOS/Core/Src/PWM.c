/*
 * PWM.c
 */

#include "libraries.h"
#include "PWM.h"
#include "main.h"
#include "GPIO.h"
#include "TIMER.h"

void USER_PWM_Init( void )
{
  USER_GPIO_Define( PORTB, 6, OUT_10, OUT_AF_PP );	 // Pin PB6 as alternate function push-pull, max speed 10 MHz
  USER_GPIO_Write( PORTB, 6, 0 );

  USER_TIM_Init( TIM_4 );
}

void USER_PWM_Generate( uint16_t PSC, uint16_t ARR, uint16_t CCR1 )
{
  TIM4->PSC	=	PSC;				// Configure the prescaler, the period and the duty cycle
  TIM4->ARR	=	ARR;				//	register values
  TIM4->CCR1	=	CCR1;

  TIM4->EGR	|=	TIM_EGR_UG;			// Generate the UEV-event to load the period, the prescaler and
  							//	reset the counter

  TIM4->SR	&=	~(TIM_SR_UIF);			// Clear the Timer overflow UEV-event flag

  TIM4->CCER	|=	TIM_CCER_CC1E;			// Enable the PWM signal output and set the polarity
  TIM4->CCER	&=	~(TIM_CCER_CC1P);

  //while( !( TIM4->SR & TIM_SR_UIF ) );		// Wait for UIF
}
