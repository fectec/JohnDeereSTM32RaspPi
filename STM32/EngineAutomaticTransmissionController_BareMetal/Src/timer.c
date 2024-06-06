/*
 * TIMER.c
 */

#include "libraries.h"
#include "TIMER.h"
#include "main.h"
#include "GPIO.h"

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
    TIM3->DIER 		|=	TIM_DIER_UIE;		// Step 4 - Enable Update Interrupt
    NVIC->ISER[0]	|=	NVIC_ISER_29;		// Step 5 - Enable interrupt
  }
  else if( TIM == 2 )
  {
    RCC->APB1ENR 	|= 	RCC_APB1ENR_TIM4EN;	// Clock enable for TIM4

    TIM4->CR1		&=	~(TIM_CR1_UDIS);	// Step 1 - UEV enabled
    TIM4->CR1		&=	~(TIM_CR1_URS);		// 	UEV also by software
    TIM4->CR1		&=	~(TIM_CR1_DIR);		// 	Counter as upcounter
    TIM4->CR1		&=	~(TIM_CR1_CMS);		// 	Edge-aligned mode
    TIM4->CR1		|=	TIM_CR1_ARPE;		//	Load ARR only on UEV

    TIM4->CCMR1		&=	~(TIM_CCMR1_CC1S);	// Step 2 - CC1 channel as output
    TIM4->CCMR1		|=	TIM_CCMR1_OC1PE;	//	CCRx load in UEV event
    TIM4->CCMR1		&=	~(TIM_CCMR1_OC1M_0);	//	PWM mode 1
    TIM4->CCMR1		|=	TIM_CCMR1_OC1M_2_1;
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
  }
  else if( TIM == 1 )
  {
    if( !( TIM3->CR1 & TIM_CR1_CEN ) && !( TIM3->SR & TIM_SR_UIF ) )
    {
      TIM3->PSC	=	TIM_PSC;
      TIM3->CNT	=	TIM_CNT;

      TIM3->CR1	|=	TIM_CR1_CEN;			// Enable TIM3 timer to start counting
    }
  }
  else if( TIM == 2 )
  {
    TIM4->PSC	=	TIM_PSC;
    TIM4->CNT	=	TIM_CNT;

    TIM4->CR1	|=	TIM_CR1_CEN;			// Enable TIM4 timer to start counting
  }
}

void TIM3_IRQHandler( void )
{
  if( TIM3->SR & TIM_SR_UIF )      			// Wait for UIF
  {
    TIM3->CR1	&=	~(TIM_CR1_CEN);			// Stop TIM3 timer

    USER_GPIO_Toggle( PORTC, 2 );
    USER_GPIO_Toggle( PORTC, 3 );

    TIM3->SR	&=	~(TIM_SR_UIF);			// Clear UIF
  }
}
