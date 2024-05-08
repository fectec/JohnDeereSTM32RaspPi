/*
* timer.h
*/

#ifndef TIMER_H_
#define TIMER_H_

/*
* For Time = 1 s, Fosc = 8 MHz and Tosc = 125 ns
* CNT = 495
* PSC = 122
*/

// Timer configuration bits and counter / prescaler register values

#define TIM_SMCR_SMS	( 0x7UL << 0U )
#define TIM_CR1_UDIS	( 0x1UL << 1U )
#define TIM_CR1_DIR	( 0x1UL << 4U )
#define TIM_CR1_CMS	( 0x3UL << 5U )
#define TIM_SR_UIF	( 0x1UL << 0U )
#define TIM_CNT		0x1EF
#define TIM_PSC		0x7A
#define TIM_CR1_CEN	( 0x1UL << 0U )

// Function prototypes for TIM2 timer

void USER_TIM2_Init( void );	// Initialize TIM2 timer
void USER_TIM2_Delay( void );	// Function to generate 1 s delay via TIM2 timer

#endif /* TIMER_H_ */
