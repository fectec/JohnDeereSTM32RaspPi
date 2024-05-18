/*
 * main.c
 */

#include "main.h"
#include "GPIO.h"
#include "SYSTICK.h"
#include "I2C.h"
#include "OLED.h"

uint8_t data[2] = {0x00, 0x02};

int main( void )
{
  RCC->APB2ENR	|=	RCC_APB2ENR_IOPBEN;

  USER_SYSTICK_Init();
  //USER_I2C_Init(2, I2C_FM);
  USER_OLED_Init(1);

  for(;;)
  {

  }

}
