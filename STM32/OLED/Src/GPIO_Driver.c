/*
 * GPIO_Driver.c
 */

#include "main.h"
#include "GPIO_Driver.h"

void USER_GPIO_Define(uint8_t port, uint8_t pin, uint8_t direction, uint8_t option)
{
  volatile uint32_t * CR;
  uint8_t actual_pin = pin;
  uint8_t offset = 0x00;

  if( pin > 7 ) {
      actual_pin -= 8;
      offset = 0x01;
  }

  if( port == 0 ) {
      CR = (volatile uint32_t *) (&GPIOA->CRL + offset);
  }
  else if( port == 1 ) {
      CR = (volatile uint32_t *) (&GPIOB->CRL + offset);
  }
  else if ( port == 2 ) {
      CR = (volatile uint32_t *) (&GPIOC->CRL + offset);
  }
  else if ( port == 3 ) {
      CR = (volatile uint32_t *) (&GPIOD->CRL + offset);
  }
  else if( port == 4 ) {
      CR = (volatile uint32_t *) (&GPIOE->CRL + offset);
  }
  else if( port == 5 ) {
      CR = (volatile uint32_t *) (&GPIOF->CRL + offset);
  }
  else {
      CR = (volatile uint32_t *) (&GPIOG->CRL + offset);
  }

  *CR	&=	~( 0xF << (actual_pin * 4) );		// Reset the target pin
  *CR	|=	( direction << (actual_pin * 4) )	// Set up the direction and the option for the pin
	|	( option << (actual_pin * 4 + 2) );
}

uint8_t USER_GPIO_Read(uint8_t port, uint8_t pin)
{
  volatile uint32_t * IDR;
  int state;

  if( port == 0 ) {
      IDR = (volatile uint32_t *) (&GPIOA->IDR);
  }
  else if( port == 1 )
  {
      IDR = (volatile uint32_t *) (&GPIOB->IDR);
  }
  else if( port == 2 )
  {
      IDR = (volatile uint32_t *) (&GPIOC->IDR);
  }
  else if( port == 3 )
  {
      IDR = (volatile uint32_t *) (&GPIOD->IDR);
  }
  else if( port == 4 )
  {
      IDR = (volatile uint32_t *) (&GPIOE->IDR);
  }
  else if( port == 5 )
  {
      IDR = (volatile uint32_t *) (&GPIOF->IDR);
  }
  else
  {
      IDR = (volatile uint32_t *) (&GPIOG->IDR);
  }

  state = ( ( *IDR & ( 1 << pin ) ) >> pin );
  return state;
}

void USER_GPIO_Write(uint8_t port, uint8_t pin, uint8_t state)
{
  volatile uint32_t * ODR;

  if( port == 0 ) {
      ODR = (volatile uint32_t *) (&GPIOA->ODR);
  }
  else if( port == 1 )
  {
      ODR = (volatile uint32_t *) (&GPIOB->ODR);
  }
  else if( port == 2 )
  {
      ODR = (volatile uint32_t *) (&GPIOC->ODR);
  }
  else if( port == 3 )
  {
      ODR = (volatile uint32_t *) (&GPIOD->ODR);
  }
  else if( port == 4 )
  {
      ODR = (volatile uint32_t *) (&GPIOE->ODR);
  }
  else if( port == 5 )
  {
      ODR = (volatile uint32_t *) (&GPIOF->ODR);
  }
  else
  {
      ODR = (volatile uint32_t *) (&GPIOG->ODR);
  }

  state ? ( *ODR |= ( state << pin ) ) : ( *ODR &= ~( 1 << pin ) );
}

void USER_GPIO_Toggle(uint8_t port, uint8_t pin)
{
  if( USER_GPIO_Read(port, pin) ) {
      USER_GPIO_Write(port, pin, 0);
  }
  else {
      USER_GPIO_Write(port, pin, 1);
  }
}