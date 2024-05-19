/*
 * matrixkeyboard.c
 */

#include "libraries.h"
#include "matrix_keypad.h"
#include "main.h"
#include "GPIO.h"

// PB10, PB6, PB5, PB7

uint8_t R_POSITIONS[NUMBER_OF_ELEMENTS] = {10, 6, 5, 7};

// PB1, PB15, PB14, PB13

uint8_t C_POSITIONS[NUMBER_OF_ELEMENTS] = {1, 15, 14, 13};

char keys[NUMBER_OF_ELEMENTS][NUMBER_OF_ELEMENTS] =
{
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Initialize matrix keypad

void USER_MATRIX_KEYPAD_Init( void )
{
  // Pin PB10 (Row 1) as general purpose output push-pull, max speed 50 MHz

  USER_GPIO_Define( PORTB, 10, OUT_50, OUT_GP_PP );
  USER_GPIO_Write( PORTB, 10, 1 );

  // Pin PB6 (Row 2) as general purpose output push-pull, max speed 50 MHz

  USER_GPIO_Define( PORTB, 6, OUT_50, OUT_GP_PP );
  USER_GPIO_Write( PORTB, 6, 1 );

  // Pin PB5 (Row 3) as general purpose output push-pull, max speed 50 MHz

  USER_GPIO_Define( PORTB, 5, OUT_50, OUT_GP_PP );
  USER_GPIO_Write( PORTB, 5, 1 );

  // Pin PB7 (Row 4) as general purpose output push-pull, max speed 50 MHz

  USER_GPIO_Define( PORTB, 7, OUT_50, OUT_GP_PP );
  USER_GPIO_Write( PORTB, 7, 1 );

  // Pin PB1 (Col 1) as input pull up

  USER_GPIO_Define( PORTB, 1, INP, INP_PP );
  USER_GPIO_Write( PORTB, 1, 1 );

  // Pin PB15 (Col 2) as input pull up

  USER_GPIO_Define( PORTB, 15, INP, INP_PP );
  USER_GPIO_Write( PORTB, 15, 1 );

  // Pin PB14 (Col 3) as input pull up

  USER_GPIO_Define( PORTB, 14, INP, INP_PP );
  USER_GPIO_Write( PORTB, 14, 1 );

  // Pin PB13 (Col 4) as input pull up

  USER_GPIO_Define( PORTB, 13, INP, INP_PP );
  USER_GPIO_Write( PORTB, 13, 1 );
}

// Read matrix keypad

char USER_MATRIX_KEYPAD_Read( void )
{
  char selectedKey = 'N';				// Default character

  for (uint8_t i = 0; i < NUMBER_OF_ELEMENTS; i++)
  {
    GPIOB->BSRR = (1 << (R_POSITIONS[i] + 16));

    for (uint8_t j = 0; j < NUMBER_OF_ELEMENTS; j++)
    {
	if ((GPIOB->IDR & (1 << C_POSITIONS[j])) == 0)
	{
	    selectedKey = keys[i][j];
	}
    }

    GPIOB->BSRR = (1 << R_POSITIONS[i]);
  }

  return selectedKey;
}
