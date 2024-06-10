/*
 * TIMER.h
 */

#ifndef TIMER_H_
#define TIMER_H_

// TIM selection

#define TIM_2			0
#define TIM_3			1
#define TIM_4			2

// Timer peripheral configuration bit for interruption

#define NVIC_ISER_29		0x1UL << 29U

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
