/*
 * main.c
 */

#include "main.h"
#include "GPIO.h"
#include "SYSTICK.h"
#include "I2C.h"

uint8_t data[2] = {0x00, 0x02};

int main( void )
{
  USER_SYSTICK_Init();
  USER_I2C_Init(2, I2C_FM);

  for(;;)
  {
    USER_I2C_Write(2, 0x76, data);
  }

}
