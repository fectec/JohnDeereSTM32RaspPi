/*
 * SYSTICK.c
 */

#include "libraries.h"
#include "SYSTICK.h"
#include "main.h"

// Initialize SysTick

void USER_SYSTICK_Init( void )
{
    SYSTICK->CTRL	= 0;				// Clear register
    SYSTICK->LOAD	= 0x00FFFFFF;			// Max start value
    SYSTICK->VAL	= 0;				// Clear register

    SYSTICK->CTRL	|=	SYSTICK_CTRL_CLKSOURCE;	// Clock source is processor clock (AHB)
    SYSTICK->CTRL	|=	SYSTICK_CTRL_ENABLE;	// Counter enabled
}

// Generate 1 millisecond delay via SysTick

void USER_SYSTICK_Delay_Millis( void )
{
  SYSTICK->LOAD		=	SYSTICK_LOAD;
  SYSTICK->VAL		=	0;
  while(!(SYSTICK->CTRL & SYSTICK_CTRL_COUNTFLAG));	// Returns 1 if timer counted to 0 since last time this was read
}

// Generate milliseconds delay via SysTick

void USER_SYSTICK_Delay_ms( uint32_t t )
{
  for(; t > 0; t--)
  {
      USER_SYSTICK_Delay_Millis();
  }
}
