/*
 * LEDS.c
 */

#include "libraries.h"
#include "LEDS.h"
#include "main.h"
#include "GPIO.h"

void USER_LEDS_Init( void )
{
  // Pin PC2 as general purpose output push-pull, max speed 50 MHz

  USER_GPIO_Define( PORTC, 2, OUT_50, OUT_GP_PP );
  USER_GPIO_Write( PORTC, 2, 0 );

  // Pin PC3 as general purpose output push-pull, max speed 50 MHz

  USER_GPIO_Define( PORTC, 3, OUT_50, OUT_GP_PP );
  USER_GPIO_Write( PORTC, 3, 0 );
}
