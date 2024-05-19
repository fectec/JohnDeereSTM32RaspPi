/*
 * I2C.c
 */

#include "libraries.h"
#include "I2C.h"
#include "main.h"
#include "GPIO.h"

// Initialize I2C

void USER_I2C_Init( uint8_t I2C, uint8_t speed_mode )
{
  RCC->APB2ENR		|=	RCC_APB2ENR_AFIOEN;	// Alternate function I/O clock enable

  if( I2C == 0 )
  {
      RCC->APB1ENR 	|=	RCC_APB1ENR_I2C1EN;	// I2C1 clock enable

      USER_GPIO_Define( PORTB, 6, OUT_50, OUT_AF_OD );	// PB6 I2C1_SCL
      USER_GPIO_Define( PORTB, 7, OUT_50, OUT_AF_OD );	// PB7 I2C1_SDA

      I2C1->CR1		|=	I2C_CR1_SWRST;		// Software reset
      I2C1->CR1		&=	~I2C_CR1_SWRST;

      I2C1->CR2		=	I2C_CR2_FREQ;		// Peripheral clock frequency of 8 MHz

      I2C1->CCR		=	speed_mode;		// Clock control register in Fm/Sm mode
      I2C1->TRISE	=	I2C_TRISE_TRISE;	// Maximum rise time in Fm/Sm mode (Master mode)

      I2C1->CR1		|=	I2C_CR1_PE;		// Peripheral enable
  }
  else if( I2C == 1 )
  {
      RCC->APB1ENR 	|=	RCC_APB1ENR_I2C2EN;	// I2C2 clock enable

      USER_GPIO_Define( PORTB, 10, OUT_50, OUT_AF_OD );	// PB10 I2C2_SCL
      USER_GPIO_Define( PORTB, 11, OUT_50, OUT_AF_OD );	// PB11 I2C2_SDA

      I2C2->CR1		|=	I2C_CR1_SWRST;
      I2C2->CR1		&=	~I2C_CR1_SWRST;

      I2C2->CR2		=	I2C_CR2_FREQ;

      I2C2->CCR		=	speed_mode;
      I2C2->TRISE	=	I2C_TRISE_TRISE;

      I2C2->CR1		|=	I2C_CR1_PE;
  }

}

// Start I2C

void USER_I2C_Start( uint8_t I2C )
{

  if( I2C == 0 )
  {
      I2C1->CR1		|=	I2C_CR1_START;		// Start generation
      while (! ( I2C1->SR1 & I2C_SR1_SB) );		// Set when a Start condition generated
  }
  else if ( I2C == 1 )
  {
      I2C2->CR1		|=	I2C_CR1_START;
      while (! ( I2C2->SR1 & I2C_SR1_SB ) );
  }

}

// Send the address + R or W via I2C

void USER_I2C_Address( uint8_t I2C, uint8_t address, uint8_t RW )
{
  volatile uint16_t tmp;

  if( I2C == 0 )
  {
      I2C1->DR = ( address | RW );

      while( !( I2C1->SR1 & I2C_SR1_ADDR ) );		// ADDR flag is zero while address is mismatched or not received
      while ( I2C1->SR1 & I2C_SR1_ADDR )		// ADDR flag is set when received address matched
      {
	  tmp = I2C1->SR1;				// Reading I2C_SR2 after reading I2C_SR1 clears the ADDR flag
	  tmp = I2C1->SR2;

	  if( !( I2C1->SR1 & I2C_SR1_ADDR ) )
	  {
	      break;
	  }
      }
  }
  else if ( I2C == 1 )
  {
      I2C2->DR = ( address | RW );

      while( !( I2C2->SR1 & I2C_SR1_ADDR ) );
      while ( I2C2->SR1 & I2C_SR1_ADDR )
      {
	  tmp = I2C2->SR1;
	  tmp = I2C2->SR2;

	  if( !( I2C2->SR1 & I2C_SR1_ADDR ) )
	  {
	      break;
	  }
      }
  }

}

// Send data via I2C

void USER_I2C_Data( uint8_t I2C, uint8_t data )
{

  if( I2C == 0 )
  {
      while( !( I2C1->SR1 & I2C_SR1_TXE ) );		// While data register not empty
      I2C1->DR = data;
      while( !( I2C1->SR1 & I2C_SR1_TXE ) );
  }
  else if ( I2C == 1 )
  {
      while( !( I2C2->SR1 & I2C_SR1_TXE ) );		// While data register not empty
      I2C2->DR = data;
      while( !( I2C2->SR1 & I2C_SR1_TXE ) );
  }

}

// Stop I2C

void USER_I2C_Stop( uint8_t I2C )
{
  volatile uint16_t tmp;

  if( I2C == 0 )
  {
      tmp = I2C1->SR1;
      tmp = I2C1->SR2;
      I2C1->CR1		|=	I2C_CR1_STOP;		// Stop generation
  }
  else if ( I2C == 1 )
  {
      tmp = I2C2->SR1;
      tmp = I2C2->SR2;
      I2C2->CR1		|=	I2C_CR1_STOP;		// Stop generation
  }

}

// Write data via I2C

void USER_I2C_Write( uint8_t I2C, uint8_t address, uint8_t data[] )
{
  uint32_t i = 0;

  USER_I2C_Start( I2C );
  USER_I2C_Address( I2C, address, 0 );

  while(data[i])
  {
    USER_I2C_Data( I2C, data[i] );
    i++;
  }

  USER_I2C_Stop( I2C );
}
