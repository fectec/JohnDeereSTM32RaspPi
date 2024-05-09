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
	TIM2->CNT	=	TIM_CNT;		//	Step 4 - Configure initial count and prescaler
	TIM2->PSC	=	TIM_PSC;
}

void USER_TIM2_Delay( void ) {

	TIM2->CR1	|=	TIM_CR1_CEN;		//	Enable TIM2 timer to start counting

	while(!( TIM2->SR & TIM_SR_UIF ));		//	Wait for UIF
	TIM2->CR1	&=	~(TIM_CR1_CEN);		//	Stop TIM2 timer

	TIM2->SR	&=	~(TIM_SR_UIF);		//	Clear UIF
	TIM2->CNT	=	TIM_CNT;		//	Re-charge initial count
}
