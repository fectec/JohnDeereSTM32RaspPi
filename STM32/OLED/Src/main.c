/*
 * main.c
 */

#include "main.h"
#include "GPIO_Driver.h"
#include "systick.h"

void USER_Delay( void );

int main(void)
{
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	// PORTA Clock Enable
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;	// PORTC Clock Enable

  // PA5 as OUT 10 MHz

  USER_GPIO_Define(PORTA, 5, OUT_10, OUT_GP_PP);
  USER_GPIO_Write(PORTA, 5, 0);

  // PC13 as INP pull-up

  USER_GPIO_Define(PORTC, 13, INP, INP_PP);
  USER_GPIO_Write(PORTC, 13, 1);

  for (;;) {
    if( !USER_GPIO_Read(PORTC, 13) )
    {
	USER_SYSTICK_Delay(1);

	if( !USER_GPIO_Read(PORTC, 13) )
	{
	    USER_GPIO_Toggle(PORTA, 5);
	    while( !USER_GPIO_Read(PORTC, 13) ){ }
	    USER_SYSTICK_Delay(1);
	}
    }
  }
}

void USER_Delay( void ){
  __asm("LDR r0, =250000");
  __asm("again: sub r0, r0, #1");
  __asm("CMP r0, #0");
  __asm("BNE again");
}
