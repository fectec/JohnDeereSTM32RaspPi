/*
 * timer.c
 */

#include "main.h"
#include "timer.h"

void USER_TIM2_Init( void ) {

	TIM2->SMCR	&=	~(TIM_SMCR_SMS);	//	Step 1 - Enable internal clock source
	TIM2->CR1	&=	~(TIM_CR1_UDIS);	//	Step 2 - UEV enabled
	TIM2->CR1	&=	~(TIM_CR1_DIR);		// 		Counter as upcounter
	TIM2->CR1	&=	~(TIM_CR1_CMS);		//		Edge-aligned mode
	TIM2->SR	&=	~(TIM_SR_UIF);		//	Step 3 - Clear Update Interrupt Flag
}

void USER_TIM2_Delay( uint16_t TIM_PSC, uint16_t TIM_CNT ) {

	TIM2->PSC	=	TIM_PSC;		//	Configure initial prescaler and count values
	TIM2->CNT	=	TIM_CNT;

	TIM2->CR1	|=	TIM_CR1_CEN;		//	Enable TIM2 timer to start counting

	while(!( TIM2->SR & TIM_SR_UIF ));		//	Wait for UIF
	TIM2->CR1	&=	~(TIM_CR1_CEN);		//	Stop TIM2 timer

	TIM2->SR	&=	~(TIM_SR_UIF);		//	Clear UIF
}
