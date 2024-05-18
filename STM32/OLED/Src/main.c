/*
 * main.c
 */

#include "main.h"
#include "GPIO.h"
#include "SYSTICK.h"
#include "I2C.h"
#include "OLED.h"

int main( void )
{
  RCC->APB2ENR	|=	RCC_APB2ENR_IOPBEN;

  USER_OLED_Init_64(I2C_1);
  USER_OLED_Blank(I2C_1);
  USER_OLED_Message(I2C_1, "TEST", OLED_SCREEN_COLUMNS / 4, OLED_SCREEN_ROWS / 2);

  for(;;)
  {

  }
}
