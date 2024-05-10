/*
 * timer.h
 */

#ifndef TIMER_H_
#define TIMER_H_

// Timer configuration bits and

#define TIM_SMCR_SMS	( 0x7UL << 0U )
#define TIM_CR1_UDIS	( 0x1UL << 1U )
#define TIM_CR1_DIR	( 0x1UL << 4U )
#define TIM_CR1_CMS	( 0x3UL << 5U )
#define TIM_SR_UIF	( 0x1UL << 0U )
#define TIM_CR1_CEN	( 0x1UL << 0U )

// Prescaler / count register values

#define TIM_PSC_500MS	0X1E8
#define TIM_CNT_500MS	0X60

#define TIM_PSC_200MS	0xC3
#define TIM_CNT_200MS	0xE6

#define TIM_PSC_50MS	0X30
#define TIM_CNT_50MS	0XE6

#define TIM_PSC_41MS	0X28
#define TIM_CNT_41MS	0X600

#define TIM_PSC_5MS	0X4
#define TIM_CNT_5MS	0X600

#define TIM_PSC_1MS	0X0
#define TIM_CNT_1MS	0X600

#define TIM_PSC_10US	0X0
#define TIM_CNT_10US	0XFD80

#define TIM_PSC_100US	0X0
#define TIM_CNT_100US	0XE700

// Function prototypes for TIM2 timer

void USER_TIM2_Init( void );			// Initialize TIM2 timer
void USER_TIM2_Delay( uint16_t, uint16_t );	// Function to generate delay via TIM2 timer

#endif /* TIMER_H_ */