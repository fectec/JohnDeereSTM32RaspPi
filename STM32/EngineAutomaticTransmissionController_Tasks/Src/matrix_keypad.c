/*
 * matrixkeyboard.c
 */

#include "libraries.h"
#include "matrix_keypad.h"
#include "main.h"
#include "GPIO.h"

// PC5, PA12, PA11, PB12

uint8_t R_POSITIONS[NUMBER_OF_ELEMENTS] = {5, 12, 11, 12};

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
  // Pin PC5 (Row 1) as general purpose output push-pull, max speed 50 MHz

  USER_GPIO_Define( PORTC, 5, OUT_50, OUT_GP_PP );
  USER_GPIO_Write( PORTC, 5, 1 );

  // Pin PA12 (Row 2) as general purpose output push-pull, max speed 50 MHz

  USER_GPIO_Define( PORTA, 12, OUT_50, OUT_GP_PP );
  USER_GPIO_Write( PORTA, 12, 1 );

  // Pin PA11 (Row 3) as general purpose output push-pull, max speed 50 MHz

  USER_GPIO_Define( PORTA, 11, OUT_50, OUT_GP_PP );
  USER_GPIO_Write( PORTA, 11, 1 );

  // Pin PB12 (Row 4) as general purpose output push-pull, max speed 50 MHz

  USER_GPIO_Define( PORTB, 12, OUT_50, OUT_GP_PP );
  USER_GPIO_Write( PORTB, 12, 1 );

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
    if( i == 0 )
    {
       GPIOC->BSRR = (1 << (R_POSITIONS[i] + 16));
    }
    else if( i == 3 )
    {
       GPIOB->BSRR = (1 << (R_POSITIONS[i] + 16));
    }
    else
    {
       GPIOA->BSRR = (1 << (R_POSITIONS[i] + 16));
    }

    for (uint8_t j = 0; j < NUMBER_OF_ELEMENTS; j++)
    {
      if ((GPIOB->IDR & (1 << C_POSITIONS[j])) == 0)
      {
	  selectedKey = keys[i][j];
      }
    }

    if( i == 0 )
    {
      GPIOC->BSRR = (1 << R_POSITIONS[i]);
    }
    else if( i == 3 )
    {
      GPIOB->BSRR = (1 << R_POSITIONS[i]);
    }
    else
    {
      GPIOA->BSRR = (1 << R_POSITIONS[i]);
    }
  }

  return selectedKey;
}
