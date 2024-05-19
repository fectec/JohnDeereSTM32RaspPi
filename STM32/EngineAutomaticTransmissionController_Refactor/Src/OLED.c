/*
 * OLED.c
 */

#include "libraries.h"
#include "OLED.h"
#include "I2C.h"
#include "SYSTICK.h"

// Send a 1 byte command to the OLED

void USER_OLED_Command_1_Byte( uint8_t I2C, uint8_t data )
{
  USER_I2C_Start( I2C );
  USER_I2C_Address( I2C, OLED_PRIMARY_ADDRESS, 0 );

  USER_I2C_Data( I2C, 0x00 );				// Control function for a command
  USER_I2C_Data( I2C, data );

  USER_I2C_Stop( I2C );
}

// Send a 2 byte command to the OLED

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

// Initialize OLED

void USER_OLED_Init( uint8_t I2C, uint8_t screen_size )
{
  USER_I2C_Init( I2C, I2C_FM );

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

// Initialize 128x32 OLED

void USER_OLED_Init_32( uint8_t I2C )
{
  USER_OLED_Init(I2C, 0x22);
}

// Initialize 128x64 OLED

void USER_OLED_Init_64( uint8_t I2C )
{
  USER_OLED_Init(I2C, 0x12);
}

// Send data to OLED

void USER_OLED_Data( uint8_t I2C, uint8_t data )
{
  USER_I2C_Start( I2C );
  USER_I2C_Address( I2C, OLED_PRIMARY_ADDRESS, 0 );

  USER_I2C_Data( I2C, 0x40 );				// Control function for data
  USER_I2C_Data( I2C, data );

  USER_I2C_Stop( I2C );
}

// Send screen position to OLED

void USER_OLED_Position( uint8_t I2C, uint8_t x_pos, uint8_t y_pos )
{
  USER_OLED_Command_1_Byte( I2C, 0x00 + ( 0x0F & x_pos ) );
  USER_OLED_Command_1_Byte( I2C, 0x10 + (0x0F & ( x_pos >> 4 ) ) );
  USER_OLED_Command_1_Byte( I2C, 0xB0 + y_pos );
}

// Clear OLED screen

void USER_OLED_Blank( uint8_t I2C )
{
  uint8_t i, j;

  USER_OLED_Position( I2C, 0, 0 );

  for(i = 0; i < OLED_SCREEN_ROWS; i++)
  {
    for(j = 0; j < OLED_SCREEN_COLUMNS; j++)
    {
	USER_OLED_Data( I2C, 0x0 );
    }
  }
}

// Print a string on the OLED screen

void USER_OLED_Print( uint8_t I2C, char str[] )
{
  uint8_t i = 0, j;

  while( str[i] )
  {
      for(j = 0; j < 5; j++)
      {
	   USER_OLED_Data(I2C, ASCII[str[i] - 32][j]);
      }

      i++;
  }
}

// Print a message (a string with a defined position) on the OLED screen

void USER_OLED_Message( uint8_t I2C, char str[], uint8_t x_pos, uint8_t y_pos )
{
  USER_OLED_Position(I2C, x_pos, y_pos);
  USER_OLED_Print(I2C, str);
}

// Clear OLED buffer

void USER_OLED_Clear_Buffer( char screen_buffer[OLED_SCREEN_ROWS][OLED_SCREEN_COLUMNS] )
{
  uint8_t i, j;

  for(i = 0; i < OLED_SCREEN_ROWS; i++)
  {
      for(j = 0; j < OLED_SCREEN_COLUMNS; j++)
      {
	  screen_buffer[i][j] = 0;
      }
  }
}

// Update OLED buffer

void USER_OLED_Update_Buffer( ImgType img, uint8_t img_num, char screen_buffer[OLED_SCREEN_ROWS][OLED_SCREEN_COLUMNS] )
{
  uint16_t x_dir, y_dir, end_x, end_y, cnt = 0;

  if( ( img.width + img.x_pos ) > OLED_SCREEN_COLUMNS )
  {
      end_x = OLED_SCREEN_COLUMNS - 1;
  }
  else
  {
      end_x = img.width + img.x_pos - 1;
  }

  if( ( img.height + img.y_pos ) > OLED_SCREEN_ROWS )
  {
      end_y = OLED_SCREEN_ROWS - 1;
  }
  else
  {
      end_y = img.height + img.y_pos - 1;
  }

  for(y_dir = img.y_pos; y_dir <= end_y; y_dir++)
  {
    for (x_dir= img.x_pos; x_dir <= end_x; x_dir++)
    {
      cnt =( y_dir - img.y_pos ) * img.width + x_dir - img.x_pos;
      screen_buffer[y_dir][x_dir] = img.image[img_num][cnt];
    }
  }
}

// Update OLED string buffer

void USER_OLED_Update_String_Buffer( uint8_t x_pos, uint8_t y_pos, char str[], char screen_buffer[OLED_SCREEN_ROWS][OLED_SCREEN_COLUMNS] )
{
  uint8_t i = 0, j, cnt_col = x_pos, cnt_row = y_pos;

  while( str[i] )
  {
    if( cnt_row > OLED_SCREEN_ROWS ) { break; }

    for(j = 0; j < 5; j++)
    {
      screen_buffer[cnt_row][cnt_col] = ASCII[str[i] - 32][j];

      if( ( cnt_col + 1 ) > OLED_SCREEN_COLUMNS - 1 )
      {
	if( ( cnt_row + 1 ) > OLED_SCREEN_ROWS )
	{
	    break;
	}
	else
	{
	    cnt_row ++;
	    cnt_col = x_pos;
	}
      }
      else
      {
	    cnt_col ++;
      }
    }

    i++;
  }
}

// Print OLED buffer

void USER_OLED_Print_Buffer( uint8_t I2C, char screen_buffer[OLED_SCREEN_ROWS][OLED_SCREEN_COLUMNS] )
{
  USER_OLED_Position( I2C, 0, 0 );

  uint8_t i, j;

  for (i = 0; i < OLED_SCREEN_ROWS; i++)
  {
    for(j = 0; j < OLED_SCREEN_COLUMNS; j++)
    {
	USER_OLED_Data( I2C, screen_buffer[i][j] );
    }
  }
}

// Update OLED buffer bit

void USER_OLED_Update_Buffer_Bit( ImgType img, uint8_t img_num, char screen_buffer[OLED_SCREEN_ROWS][OLED_SCREEN_COLUMNS] )
{
  int start_x, end_x, start_img_x, y_offset, bit_y_pos_byte, start_y, end_y, x_dir, y_dir,
  buffer_height = OLED_SCREEN_ROWS, buffer_width = OLED_SCREEN_COLUMNS, start_img_byte, start_img_x_tmp,
  cnt_1, cnt_2;

  // Working on the X axe

  // Find end_x

  if(img.x_pos > buffer_width)
  {
    end_x = buffer_width;
  }
  else if(img.x_pos < 1)
  {
    end_x = 0;
  }
  else
  {
    end_x = img.x_pos;
  }

  // Find start_x

  start_x = img.x_pos - img.width;

  if(start_x > buffer_width)
  {
    start_x = buffer_width;
  }
  else if(start_x < 0)
  {
    start_x = 0;
  }

  // Starting the picture x_location to start from

  start_img_x = img.width - img.x_pos;

  if(start_img_x < 0)
  {
      start_img_x = 0;
  }

  // Working on the Y axe

  y_offset = img.bit_y_pos % 8;
  bit_y_pos_byte = img.bit_y_pos / 8;

  if(bit_y_pos_byte > buffer_height)
  {
      bit_y_pos_byte = buffer_height;
  }

  // Find end_y

  end_y = buffer_height - bit_y_pos_byte + 1;

  if(end_y < 0)
  {
    end_y = buffer_height;
  }
  else
  {
    end_y = bit_y_pos_byte + 1;
  }

  // Find start_y

  start_y = img.bit_y_pos / 8 - img.height;

  if(start_y > buffer_height)
  {
    start_y = buffer_height;
  }
  else if(start_y < 0)
  {
    start_y = 0;
  }

  // Starting the picture y_location to start form

  start_img_byte = img.height - bit_y_pos_byte - 1;

  if(start_img_byte < 0)
  {
    start_img_byte = -1;
  }

  // Running the display

  for(y_dir = start_y; y_dir < end_y; y_dir++)
  {
    start_img_x_tmp = start_img_x;

    for(x_dir = start_x; x_dir < end_x; x_dir++)
    {
      if(start_img_byte == -1)
      {
	cnt_1 = start_img_x;
      }
      else
      {
	cnt_1 = (start_img_byte) * img.width + start_img_x_tmp;
      }

      cnt_2 = (start_img_byte + 1) * img.width + start_img_x_tmp;
      start_img_x_tmp++;

      // Start drawing

      if(start_img_byte == -1)
      {
	// Beginning of the picture

	screen_buffer[y_dir][x_dir] = ( img.image[img_num][cnt_2] << ( y_offset ) );
      }
      else if(start_img_byte < img.height - 1)
      {
	  // Inside of the picture

	  screen_buffer[y_dir][x_dir] = ( img.image[img_num][cnt_2] << ( y_offset ) ) | ( img.image[img_num][cnt_1] >> ( 8-y_offset ) );
      }
      else
      {
	  screen_buffer[y_dir][x_dir] = ( img.image[img_num][cnt_1] >> ( 8 - y_offset ) );
      }
    }

    start_img_byte++;
  }
}

void USER_OLED_Animation( uint8_t I2C, char screen_buffer[OLED_SCREEN_ROWS][OLED_SCREEN_COLUMNS] )
{
  uint16_t i = 0;

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

  USER_OLED_Clear_Buffer( screen_buffer );
  USER_OLED_Update_Buffer( JOHN_DEERE_LOGO_PIC, 0, screen_buffer );
  USER_OLED_Print_Buffer( I2C, screen_buffer );
  USER_SYSTICK_Delay_ms( 100 );

  USER_OLED_Clear_Buffer( screen_buffer );
  USER_OLED_Update_Buffer( ITESM_LOGO_PIC, 0, screen_buffer );
  USER_OLED_Print_Buffer( I2C, screen_buffer );
  USER_SYSTICK_Delay_ms( 100 );

  USER_OLED_Clear_Buffer( screen_buffer );
  USER_OLED_Clear_Buffer( screen_buffer );
  USER_OLED_Update_Buffer( STM32_LOGO_PIC, 0, screen_buffer );
  USER_OLED_Print_Buffer( I2C, screen_buffer );
  USER_SYSTICK_Delay_ms( 100 );

  USER_OLED_Clear_Buffer( screen_buffer );
  USER_OLED_Update_Buffer( RASPBERRY_PI_LOGO_PIC, 0, screen_buffer );
  USER_OLED_Print_Buffer( I2C, screen_buffer );
  USER_SYSTICK_Delay_ms( 100 );

  USER_OLED_Clear_Buffer( screen_buffer );
  USER_OLED_Update_Buffer( LINUX_LOGO_PIC, 0, screen_buffer );
  USER_OLED_Print_Buffer( I2C, screen_buffer );
  USER_SYSTICK_Delay_ms( 100 );

  USER_OLED_Blank( I2C );
  USER_OLED_Message( I2C, "TRACTOR DRIVING", OLED_SCREEN_COLUMNS / 5, OLED_SCREEN_ROWS / 3 + TEXT_ROWS_OFFSET );
  USER_OLED_Message( I2C, "SIMULATOR", OLED_SCREEN_COLUMNS / 4 + TEXT_COLUMNS_OFFSET, OLED_SCREEN_ROWS / 2 );
  USER_SYSTICK_Delay_ms( 200 );

  for(i = 0; i < LOGO_DISPLACEMENT; i++)
  {
    JOHN_DEERE_LOGO_PIC_NO_TEXT.x_pos = 3 * i;
    JOHN_DEERE_LOGO_PIC_NO_TEXT.bit_y_pos = 2 * i;

    USER_OLED_Clear_Buffer( screen_buffer );
    USER_OLED_Update_Buffer_Bit( JOHN_DEERE_LOGO_PIC_NO_TEXT, 0, screen_buffer );
    USER_OLED_Print_Buffer( I2C, screen_buffer );
  }

  USER_SYSTICK_Delay_ms( 200 );
  USER_OLED_Clear_Buffer( screen_buffer );
  USER_OLED_Blank( I2C );
}
