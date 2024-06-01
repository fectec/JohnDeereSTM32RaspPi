/*
 * timer.c
 */

#include "libraries.h"
#include "timer.h"
#include "main.h"

// Initialize TIM timer

void USER_TIM_Init( uint8_t TIM )
{
  if( TIM == 0 )
  {
    RCC->APB1ENR 	|= 	RCC_APB1ENR_TIM2EN;	// Clock enable for TIM2

    TIM2->SMCR		&=	~(TIM_SMCR_SMS);	// Step 1 - Enable internal clock source
    TIM2->CR1		&=	~(TIM_CR1_UDIS);	// Step 2 - UEV enabled
    TIM2->CR1		&=	~(TIM_CR1_DIR);		// 	Counter as upcounter
    TIM2->CR1		&=	~(TIM_CR1_CMS);		//	Edge-aligned mode
    TIM2->SR		&=	~(TIM_SR_UIF);		// Step 3 - Clear Update Interrupt Flag
  }
  else if( TIM == 1 )
  {
    RCC->APB1ENR 	|= 	RCC_APB1ENR_TIM3EN;	// Clock enable for TIM3

    TIM3->SMCR		&=	~(TIM_SMCR_SMS);
    TIM3->CR1		&=	~(TIM_CR1_UDIS);
    TIM3->CR1		&=	~(TIM_CR1_DIR);
    TIM3->CR1		&=	~(TIM_CR1_CMS);
    TIM3->SR		&=	~(TIM_SR_UIF);
  }
  else if( TIM == 2 )
  {
    RCC->APB1ENR 	|= 	RCC_APB1ENR_TIM4EN;	// Clock enable for TIM4

    TIM4->SMCR		&=	~(TIM_SMCR_SMS);
    TIM4->CR1		&=	~(TIM_CR1_UDIS);
    TIM4->CR1		&=	~(TIM_CR1_DIR);
    TIM4->CR1		&=	~(TIM_CR1_CMS);
    TIM4->SR		&=	~(TIM_SR_UIF);
  }
  else if( TIM == 3 )
  {
    RCC->APB1ENR 	|= 	RCC_APB1ENR_TIM5EN;	// Clock enable for TIM5

    TIM5->SMCR		&=	~(TIM_SMCR_SMS);
    TIM5->CR1		&=	~(TIM_CR1_UDIS);
    TIM5->CR1		&=	~(TIM_CR1_DIR);
    TIM5->CR1		&=	~(TIM_CR1_CMS);
    TIM5->SR		&=	~(TIM_SR_UIF);
  }
}

// Generate delay via TIM timer

void USER_TIM_Delay( uint8_t TIM, uint16_t TIM_PSC, uint16_t TIM_CNT )
{
  if( TIM == 0 )
  {
    TIM2->PSC	=	TIM_PSC;			// Configure initial prescaler and count values
    TIM2->CNT	=	TIM_CNT;

    TIM2->CR1	|=	TIM_CR1_CEN;			// Enable TIM2 timer to start counting

    while(!( TIM2->SR & TIM_SR_UIF ));			// Wait for UIF
    TIM2->CR1	&=	~(TIM_CR1_CEN);			// Stop TIM2 timer

    TIM2->SR	&=	~(TIM_SR_UIF);			// Clear UIF
  }
  else if( TIM == 1 )
  {
    TIM3->PSC	=	TIM_PSC;
    TIM3->CNT	=	TIM_CNT;

    TIM3->CR1	|=	TIM_CR1_CEN;			// Enable TIM3 timer to start counting

    while(!( TIM3->SR & TIM_SR_UIF ));
    TIM3->CR1	&=	~(TIM_CR1_CEN);			// Stop TIM3 timer

    TIM3->SR	&=	~(TIM_SR_UIF);
  }
  else if( TIM == 2 )
  {
    TIM4->PSC	=	TIM_PSC;
    TIM4->CNT	=	TIM_CNT;

    TIM4->CR1	|=	TIM_CR1_CEN;			// Enable TIM4 timer to start counting

    while(!( TIM4->SR & TIM_SR_UIF ));
    TIM4->CR1	&=	~(TIM_CR1_CEN);			// Stop TIM4 timer

    TIM4->SR	&=	~(TIM_SR_UIF);
  }
  else if( TIM == 3 )
  {
    TIM5->PSC	=	TIM_PSC;
    TIM5->CNT	=	TIM_CNT;

    TIM5->CR1	|=	TIM_CR1_CEN;			// Enable TIM5 timer to start counting

    while(!( TIM5->SR & TIM_SR_UIF ));
    TIM5->CR1	&=	~(TIM_CR1_CEN);			// Stop TIM5 timer

    TIM5->SR	&=	~(TIM_SR_UIF);
  }
}
