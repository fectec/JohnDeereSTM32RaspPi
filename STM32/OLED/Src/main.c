/*
 * main.c
 */

#include "main.h"
#include "GPIO.h"
#include "SYSTICK.h"
#include "I2C.h"
#include "OLED.h"

#define TEXT_COLUMNS_OFFSET	8
#define TEXT_ROWS_OFFSET	1
#define LOGO_DISPLACEMENT	30

char oled_buffer[OLED_SCREEN_ROWS][OLED_SCREEN_COLUMNS];
uint8_t i, j;

int main( void )
{
  ImgType JOHN_DEERE_LOGO_PIC = { .height = JOHN_DEERE_LOGO_ROWS, .width = JOHN_DEERE_LOGO_COLS, .x_pos = 0, .y_pos = 0, .bit_y_pos = 0 };
  JOHN_DEERE_LOGO_PIC.image[0] = JOHN_DEERE_LOGO;

  ImgType JOHN_DEERE_LOGO_PIC_NO_TEXT = { .height = JOHN_DEERE_LOGO_NO_TEXT_ROWS, .width = JOHN_DEERE_LOGO_NO_TEXT_COLS, .x_pos = OLED_SCREEN_COLUMNS / 4, .y_pos = 0, .bit_y_pos = 0 };
  JOHN_DEERE_LOGO_PIC_NO_TEXT.image[0] = JOHN_DEERE_LOGO_NO_TEXT;

  ImgType ITESM_LOGO_PIC = { .height = ITESM_LOGO_ROWS, .width = ITESM_LOGO_COLS, .x_pos = OLED_SCREEN_COLUMNS / 4, .y_pos = 0, .bit_y_pos = 0 };
  ITESM_LOGO_PIC.image[0] = ITESM_LOGO;

  ImgType RASPBERRY_PI_LOGO_PIC = { .height = RASPBERRY_PI_LOGO_ROWS, .width = RASPBERRY_PI_LOGO_COLS, .x_pos = OLED_SCREEN_COLUMNS / 4, .y_pos = 0, .bit_y_pos = 0 };
  RASPBERRY_PI_LOGO_PIC.image[0] = RASPBERRY_PI_LOGO;

  ImgType LINUX_LOGO_PIC = { .height = LINUX_LOGO_ROWS, .width = LINUX_LOGO_COLS, .x_pos = OLED_SCREEN_COLUMNS / 4, .y_pos = 0, .bit_y_pos = 0 };
  LINUX_LOGO_PIC.image[0] = LINUX_LOGO;

  ImgType STM32_LOGO_PIC = { .height = STM32_LOGO_ROWS, .width = STM32_LOGO_COLS, .x_pos = OLED_SCREEN_COLUMNS / 4, .y_pos = 0, .bit_y_pos = 0 };
  STM32_LOGO_PIC.image[0] = STM32_LOGO;

  ImgType TRACTOR_PIC = { .height = TRACTOR_ROWS, .width = TRACTOR_COLS, .x_pos = 0, .y_pos = 0, .bit_y_pos = 0 };
  TRACTOR_PIC.image[0] = TRACTOR_1;
  TRACTOR_PIC.image[1] = TRACTOR_2;
  TRACTOR_PIC.image[2] = TRACTOR_3;
  TRACTOR_PIC.image[3] = TRACTOR_4;

  USER_SYSTICK_Init();
  RCC->APB2ENR	|=	RCC_APB2ENR_IOPBEN;

  USER_OLED_Init_64(I2C_1);

  USER_OLED_Clear_Buffer(oled_buffer);
  USER_OLED_Update_Buffer(JOHN_DEERE_LOGO_PIC, 0, oled_buffer);
  USER_OLED_Print_Buffer(I2C_1, oled_buffer);
  USER_SYSTICK_Delay_ms( 100 );

  USER_OLED_Clear_Buffer(oled_buffer);
  USER_OLED_Update_Buffer(ITESM_LOGO_PIC, 0, oled_buffer);
  USER_OLED_Print_Buffer(I2C_1, oled_buffer);
  USER_SYSTICK_Delay_ms( 100 );

  USER_OLED_Clear_Buffer(oled_buffer);
  USER_OLED_Clear_Buffer(oled_buffer);
  USER_OLED_Update_Buffer(STM32_LOGO_PIC, 0, oled_buffer);
  USER_OLED_Print_Buffer(I2C_1, oled_buffer);
  USER_SYSTICK_Delay_ms( 100 );

  USER_OLED_Clear_Buffer(oled_buffer);
  USER_OLED_Update_Buffer(RASPBERRY_PI_LOGO_PIC, 0, oled_buffer);
  USER_OLED_Print_Buffer(I2C_1, oled_buffer);
  USER_SYSTICK_Delay_ms( 100 );

  USER_OLED_Clear_Buffer(oled_buffer);
  USER_OLED_Update_Buffer(LINUX_LOGO_PIC, 0, oled_buffer);
  USER_OLED_Print_Buffer(I2C_1, oled_buffer);
  USER_SYSTICK_Delay_ms( 100 );

  USER_OLED_Blank(I2C_1);
  USER_OLED_Message(I2C_1, "TRACTOR DRIVING", OLED_SCREEN_COLUMNS / 5, OLED_SCREEN_ROWS / 3 + TEXT_ROWS_OFFSET);
  USER_OLED_Message(I2C_1, "SIMULATOR", OLED_SCREEN_COLUMNS / 4 + TEXT_COLUMNS_OFFSET, OLED_SCREEN_ROWS / 2);
  USER_SYSTICK_Delay_ms( 200 );

  for(i = 0; i < LOGO_DISPLACEMENT; i++)
  {
    JOHN_DEERE_LOGO_PIC_NO_TEXT.x_pos = 3 * i;
    JOHN_DEERE_LOGO_PIC_NO_TEXT.bit_y_pos = 2 * i;

    USER_OLED_Clear_Buffer(oled_buffer);
    USER_OLED_Update_Buffer_Bit(JOHN_DEERE_LOGO_PIC_NO_TEXT, 0, oled_buffer);
    USER_OLED_Print_Buffer(I2C_1, oled_buffer);
  }

  for(;;)
  {
    for(i = 0; i < 83; i++)
    {
	TRACTOR_PIC.x_pos = i;

      for(j = 0; j < 4; j++)
      {
	USER_OLED_Clear_Buffer(oled_buffer);
	USER_OLED_Update_Buffer(TRACTOR_PIC, j, oled_buffer);
	USER_OLED_Print_Buffer(I2C_1, oled_buffer);
      }
    }
  }

}
