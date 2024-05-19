/*
 * SYSTICK.h
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

// SysTick configuration bits

#define SYSTICK_CTRL_ENABLE	0x1UL << 0U
#define SYSTICK_CTRL_CLKSOURCE	0x1UL << 2U
#define SYSTICK_CTRL_COUNTFLAG	0x1UL << 16U

// Function prototypes for SysTick

void USER_SYSTICK_Init( void );
void USER_SYSTICK_Delay_Millis( void );
void USER_SYSTICK_Delay_ms( uint32_t );

#endif /* SYSTICK_H_ */
