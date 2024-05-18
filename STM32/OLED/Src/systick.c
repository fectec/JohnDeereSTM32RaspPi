/*
 * SYSTICK.c
 */

#include "main.h"
#include "SYSTICK.h"

void USER_SYSTICK_Init( void )
{
    SYSTICK->CTRL	= 0;				// Clear register
    SYSTICK->LOAD	= 0x00FFFFFF;			// Max start value
    SYSTICK->VAL	= 0;				// Clear register

    SYSTICK->CTRL	|=	SYSTICK_CTRL_CLKSOURCE;
    SYSTICK->CTRL	|=	SYSTICK_CTRL_ENABLE;
}

void USER_SYSTICK_Delay( uint32_t t )
{
  for(; t > 0; t--)
  {
    SYSTICK->LOAD	=	0x11940;
    SYSTICK->VAL = 0;
    while(!(SYSTICK->CTRL & SYSTICK_CTRL_COUNTFLAG));
  }
}
