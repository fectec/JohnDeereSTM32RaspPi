/*
 * systick.h
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#define SYSTICK_CTRL_ENABLE	0x1UL << 0U
#define SYSTICK_CTRL_CLKSOURCE	0x1UL << 2U
#define SYSTICK_CTRL_COUNTFLAG	0x1UL << 16U

void USER_SYSTICK_Init( void );
void USER_SYSTICK_Delay( uint32_t t );

#endif /* SYSTICK_H_ */
