/*
 * OLED.c
 */

#include "OLED.h"
#include "I2C.h"

void USER_OLED_Command_1_Byte( uint8_t I2C, uint8_t data )
{
  USER_I2C_Start( I2C );
  USER_I2C_Address( I2C, OLED_PRIMARY_ADDRESS, 0 );

  USER_I2C_Data( I2C, 0x00 );				// Control function for a command
  USER_I2C_Data( I2C, data );

  USER_I2C_Stop( I2C );
}

void USER_OLED_Command_2_Byte( uint8_t I2C, uint8_t data[] )
{
  uint8_t i = 0;

  USER_I2C_Start( I2C );
  USER_I2C_Address( I2C, OLED_PRIMARY_ADDRESS, 0 );

  USER_I2C_Data( I2C, 0x00 );	// Control function for a command
  for(i = 0; i < 2; i++)
  {
      USER_I2C_Data( I2C, data[i] );
  }

  USER_I2C_Stop( I2C );
}

void USER_OLED_Init( uint8_t I2C, uint8_t screen_size )
{
  USER_I2C_Init( I2C, I2C_SM );

  uint8_t cmd_1[] = {0xA8, 0x3F};
  USER_OLED_Command_2_Byte( I2C, cmd_1 );

  uint8_t cmd_2[] = {0xD3, 0x00};
  USER_OLED_Command_2_Byte( I2C, cmd_2 );

  USER_OLED_Command_1_Byte( I2C, 0x40 );
  USER_OLED_Command_1_Byte( I2C, 0xA1 );

  USER_OLED_Command_1_Byte( I2C, 0xC8 );

  uint8_t cmd_3[] = {0xDA, screen_size};
  USER_OLED_Command_2_Byte( I2C, cmd_3 );

  uint8_t cmd_4[] = {0x81, 0x7F};
  USER_OLED_Command_2_Byte( I2C, cmd_4 );

  USER_OLED_Command_1_Byte( I2C, 0xA4 );
  USER_OLED_Command_1_Byte( I2C, 0xA6 );

  uint8_t cmd_5[] = {0xD5, 0x80};
  USER_OLED_Command_2_Byte( I2C, cmd_5 );

  uint8_t cmd_6[] = {0x8D, 0x14};
  USER_OLED_Command_2_Byte( I2C, cmd_6 );

  USER_OLED_Command_1_Byte( I2C, 0xAF );

  uint8_t cmd_7[] = {0x20, 0x10};
  USER_OLED_Command_2_Byte( I2C, cmd_7 );
}

void USER_OLED_Init_32( uint8_t I2C )
{
  USER_OLED_Init(I2C, 0x22);
}

void USER_OLED_Init_64( uint8_t I2C )
{
  USER_OLED_Init(I2C, 0x12);
}

void USER_OLED_Data( uint8_t I2C, uint8_t data )
{
  USER_I2C_Start( I2C );
  USER_I2C_Address( I2C, OLED_PRIMARY_ADDRESS, 0 );

  USER_I2C_Data( I2C, 0x40 );				// Control function for data
  USER_I2C_Data( I2C, data );

  USER_I2C_Stop( I2C );
}

void USER_OLED_Position( uint8_t I2C, uint8_t x_pos, uint8_t y_pos )
{
  USER_OLED_Command_1_Byte( I2C, 0x00 + ( 0x0F & x_pos ) );
  USER_OLED_Command_1_Byte( I2C, 0x10 + (0x0F & ( x_pos >> 4 ) ) );
  USER_OLED_Command_1_Byte( I2C, 0xB0 + y_pos );
}


void USER_OLED_Blank( uint8_t I2C )
{
  uint8_t i, j;

  USER_OLED_Position( I2C, 0, 0 );

  for(i = 0; i < OLED_SCREEN_COLUMNS; i++)
  {
    for(j = 0; j < OLED_SCREEN_ROWS; j++)
    {
	USER_OLED_Data( I2C, 0x0 );
    }
  }
}

void USER_OLED_Print( uint8_t I2C, char str[] )
{
  uint8_t i = 0, j;

  while(str[i])
  {
      for(j = 0; j < 5; j++)
      {
	   USER_OLED_Data(I2C, ASCII[str[i] - 32][j]);
      }

      i++;
  }
}

void USER_OLED_Message( uint8_t I2C, char str[], uint8_t x_pos, uint8_t y_pos )
{
  USER_OLED_Position(I2C, x_pos, y_pos);
  USER_OLED_Print(I2C, str);
}
