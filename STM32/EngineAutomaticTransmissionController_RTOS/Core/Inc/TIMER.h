/*
 * TIMER.h
 */

#ifndef TIMER_H_
#define TIMER_H_

// TIM selection

#define TIM_2			0
#define TIM_3			1
#define TIM_4			2

// Timer peripheral configuration bits

#define TIM_SMCR_SMS		0x7UL << 0U
#define TIM_CR1_UDIS		0x1UL << 1U
#define TIM_CR1_DIR		0x1UL << 4U
#define TIM_CR1_CMS		0x3UL << 5U
#define TIM_SR_UIF		0x1UL << 0U
#define TIM_CR1_CEN		0x1UL << 0U

// For interruption

#define TIM_DIER_UIE		0x1UL << 0U
#define NVIC_ISER_29		0x1UL << 29U

// For PWM

#define TIM_CR1_URS		0x1UL << 2U
#define TIM_CR1_ARPE		0x1UL << 7U
#define TIM_CCMR1_CC1S		0x3UL << 0U
#define TIM_CCMR1_OC1PE		0x1UL << 3U
#define TIM_CCMR1_OC1M_0	0x1UL << 4U
#define TIM_CCMR1_OC1M_2_1	0x3UL << 5U
#define TIM_EGR_UG		0x1UL << 0U
#define TIM_CCER_CC1E		0x1UL << 0U
#define TIM_CCER_CC1P		0x1UL << 1U

// Timer prescaler and count register values

#define TIM_PSC_200MS		0xC3
#define TIM_CNT_200MS		0xE6

#define TIM_PSC_50MS		0X30
#define TIM_CNT_50MS		0XE6

#define TIM_PSC_40MS		0X27
#define TIM_CNT_40MS		0X600

#define TIM_PSC_10MS		0X9
#define TIM_CNT_10MS		0X600

#define TIM_PSC_5MS		0X4
#define TIM_CNT_5MS		0X600

#define TIM_PSC_1MS		0X0
#define TIM_CNT_1MS		0X600

#define TIM_PSC_10US		0X0
#define TIM_CNT_10US		0XFD80

#define TIM_PSC_100US		0X0
#define TIM_CNT_100US		0XE700

// Function prototypes for TIM timer

void USER_TIM_Init( uint8_t );
void USER_TIM_Delay( uint8_t, uint16_t, uint16_t );
void TIM3_IRQHandler( void );

#endif /* TIMER_H_ */
