/*
 * main.c
 */

#include "main.h"
#include "GPIO.h"
#include "SYSTICK.h"
#include "I2C.h"
#include "OLED.h"

char oled_buffer[OLED_SCREEN_ROWS][OLED_SCREEN_COLUMNS];
uint8_t i, j;

int main( void )
{
  USER_SYSTICK_Init();
  RCC->APB2ENR	|=	RCC_APB2ENR_IOPBEN;

  USER_OLED_Init_64(I2C_1);
  USER_OLED_Blank(I2C_1);
  USER_OLED_Message(I2C_1, "JOHN DEERE", OLED_SCREEN_COLUMNS / 4, OLED_SCREEN_ROWS / 2);
  USER_SYSTICK_Delay_ms( 200 );

  ImgType john_deere_logo_img = {.height = john_deere_logo_rows, .width = john_deere_logo_cols, .x_pos = 0, .y_pos =0};
  john_deere_logo_img.image[0] = john_deere_logo;

  USER_OLED_Clear_Buffer(oled_buffer);
  USER_OLED_Update_Buffer(john_deere_logo_img, 0, oled_buffer);
  USER_OLED_Print_Buffer(I2C_1, oled_buffer);
  USER_SYSTICK_Delay_ms( 1 );

  for(;;)
  {

  }
}
