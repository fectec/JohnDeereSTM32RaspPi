/*
 * OLED.h
 */

#ifndef OLED_H_
#define OLED_H_

// OLED defines

#define OLED_PRIMARY_ADDRESS	0x78
#define OLED_SECONDARY_ADDRESS	0x7A
#define OLED_SCREEN_ROWS	8
#define OLED_SCREEN_COLUMNS	128
#define SPRITES_NUMBER		30

// OLED drawing defines

#define TEXT_COLUMNS_OFFSET	8
#define TEXT_ROWS_OFFSET	1
#define LOGO_DISPLACEMENT	29
#define OLED_MSGS_NUMBER	5

// ImgType type

typedef struct State
{
  uint8_t height;
  uint8_t width;
  const char *image[SPRITES_NUMBER];
  int8_t x_pos;
  int8_t y_pos;
  int16_t bit_y_pos;

} ImgType;

// Function prototypes for OLED

void USER_OLED_Command_1_Byte( uint8_t, uint8_t );
void USER_OLED_Command_2_Byte( uint8_t, uint8_t[] );
void USER_OLED_Init( uint8_t, uint8_t );
void USER_OLED_Init_32( uint8_t );
void USER_OLED_Init_64( uint8_t );
void USER_OLED_Data( uint8_t, uint8_t );
void USER_OLED_Position( uint8_t, uint8_t, uint8_t );
void USER_OLED_Blank( uint8_t );
void USER_OLED_Print( uint8_t, char[] );
void USER_OLED_Message( uint8_t, char[], uint8_t, uint8_t );
void USER_OLED_Clear_Buffer( char[OLED_SCREEN_ROWS][OLED_SCREEN_COLUMNS] );
void USER_OLED_Update_Buffer( ImgType, uint8_t, char[OLED_SCREEN_ROWS][OLED_SCREEN_COLUMNS] );
void USER_OLED_Update_String_Buffer( uint8_t, uint8_t, char[], char[OLED_SCREEN_ROWS][OLED_SCREEN_COLUMNS] );
void USER_OLED_Print_Buffer( uint8_t, char[OLED_SCREEN_ROWS][OLED_SCREEN_COLUMNS] );
void USER_OLED_Update_Buffer_Bit( ImgType, uint8_t, char[OLED_SCREEN_ROWS][OLED_SCREEN_COLUMNS] );
void USER_OLED_Animation( uint8_t, char[OLED_SCREEN_ROWS][OLED_SCREEN_COLUMNS] );

// ASCII characters data

static const char ASCII[][5] =
{
 {0x00, 0x00, 0x00, 0x00, 0x00} // 20
,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c ¥
,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j
,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ?
,{0x78, 0x46, 0x41, 0x46, 0x78} // 7f ?
};

// Images data

// John Deere logo

static uint8_t JOHN_DEERE_LOGO_ROWS = 8;
static uint8_t JOHN_DEERE_LOGO_COLS = 128;
static const char JOHN_DEERE_LOGO[] =
{
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0xe0,0xf0,0x70,0x30,0x90,0xd0,0xd8,0xc8,0xe8,0xe8,0xec,0xec,0xe4,0xe4,0xe6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf7,0xf3,0xfb,0xfb,0xfb,0x7b,0xfb,0xfb,0xfb,0xfb,0xfb,0xfb,0xfb,0xfb,0xfb,0xfb,0xf3,0xf3,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xe6,0xe4,0xe4,0xec,0xec,0xe8,0xe8,0xc8,0xd8,0xd0,0x90,0xb0,0x30,0xf0,0xe0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf0,0xfc,0x3f,0x7,0xf1,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x73,0x73,0x77,0x37,0x30,0x31,0x33,0x13,0x7,0x0,0x80,0x9f,0x9f,0xcf,0xef,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0xf0,0x87,0x1f,0xfe,0xf0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0xff,0xf,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfe,0x1e,0xe,0x0,0x0,0x0,0x0,0x0,0x18,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x77,0xf,0xf,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x7,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xfc,0x80,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf3,0xf3,0xe3,0xe1,0xd1,0x91,0xb1,0x71,0x71,0xf0,0xf0,0xf0,0xf0,0xf0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xf0,0xf0,0xf0,0xf0,0xf0,0xe0,0xe0,0xc0,0x80,0x80,0x0,0x0,0x0,0x1,0x7,0xf,0x7f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0x0,0xf8,0xff,0x3f,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3,0xf,0x3f,0xf8,0xe1,0x8f,0x3f,0x7f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfe,0xfc,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfe,0xfe,0xfe,0xfc,0xfc,0xfc,0xf8,0xf9,0xf1,0x77,0x6f,0xf,0x8f,0xe3,0xf8,0x3f,0xf,0x3,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x3,0x3,0x3,0x7,0x6,0x6,0xe,0xc,0xd,0xd,0xd,0x9,0xb,0xb,0xb,0xb,0x1b,0x13,0x17,0x17,0x17,0x17,0x17,0x17,0x17,0x17,0x17,0x17,0x17,0x17,0x17,0x17,0x17,0x17,0x17,0x17,0x17,0x17,0x13,0x1b,0xb,0xb,0xb,0xb,0x9,0xd,0xd,0xd,0xc,0xe,0x6,0x6,0x7,0x3,0x3,0x3,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf0,0xf0,0xe0,0x0,0x0,0x0,0x80,0x80,0x80,0x80,0xc0,0xc0,0xc0,0x80,0x80,0x80,0x0,0x0,0x0,0x0,0x80,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0x80,0x0,0x0,0x80,0x80,0x80,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0x80,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0xf0,0xf0,0xf0,0x30,0x30,0x30,0x30,0x30,0x30,0x70,0x60,0xe0,0xc0,0xc0,0x0,0x0,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x0,0x0,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x0,0x0,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x0,0x0,0x0,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0xe0,0xc0,0xc0,0xc0,0xc0,0xc0,0xe0,0xf0,0x7f,0x3f,0xf,0x0,0x1c,0x3f,0x7f,0x63,0xe1,0xc1,0xc0,0xc1,0xc1,0xc1,0xe1,0x77,0x3f,0x1e,0x0,0x0,0xff,0xff,0xc,0x8,0x8,0x8,0x8,0x8,0x8,0xc,0xff,0xff,0x0,0x0,0x7f,0xff,0xff,0x7,0x7,0xe,0xc,0x18,0x30,0x70,0xf7,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xc0,0xc0,0xc0,0xc0,0xc0,0xe0,0xe0,0x60,0x70,0x3f,0x3f,0xf,0x0,0x7b,0xff,0xff,0xed,0xc9,0xc9,0xc9,0xc9,0xc9,0xc9,0xc1,0x0,0x0,0xff,0xff,0xff,0xc9,0xc9,0xc9,0xc9,0xc9,0xc9,0xc1,0xc1,0x0,0x0,0xff,0xff,0x7f,0x9,0x9,0x9,0x19,0x39,0x79,0xff,0xef,0xcf,0x0,0x0,0xff,0xff,0xff,0xc9,0xc9,0xc9,0xc9,0xc9,0xc9,0xc1,0xc1
};

static uint8_t JOHN_DEERE_LOGO_NO_TEXT_ROWS = 6;
static uint8_t JOHN_DEERE_LOGO_NO_TEXT_COLS = 50;
static const char JOHN_DEERE_LOGO_NO_TEXT[] =
{
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xc0,0xc0,0xc0,0xc0,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0xe0,0x78,0x8c,0xe4,0xf6,0xf6,0xfa,0xfb,0xfb,0xfd,0xfd,0xfd,0x7d,0x7e,0x5e,0x3e,0x7e,0x7e,0x1e,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xff,0xfd,0xfd,0xfd,0xfd,0xfb,0xfb,0xfa,0xf6,0xf6,0xcc,0x3c,0xf0,0x80,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0xfe,0xf,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf7,0xe7,0x67,0x7,0x3,0x3,0xc0,0xf8,0xf9,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x1,0xff,0xf8,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0xff,0x80,0xff,0xff,0xff,0xff,0xff,0xcf,0x8f,0xf,0x6f,0xc7,0xc7,0xc3,0xc0,0x80,0x80,0x80,0x80,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x83,0x3,0x3,0x0,0x0,0xd,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf,0xff,0xff,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x3,0x3f,0xf0,0x8f,0x7f,0x7f,0xff,0xff,0xff,0xff,0xff,0xfe,0xfd,0xfd,0xfb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfe,0xfc,0xfc,0xf8,0xf9,0xf9,0xf3,0xe7,0x4f,0x1f,0xc3,0xfc,0x1f,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x3,0x3,0x2,0x6,0x7,0x5,0xd,0xd,0xb,0xb,0xb,0x1b,0x1b,0x1b,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1b,0x1b,0x1b,0x1b,0xb,0xb,0xf,0xd,0x5,0x5,0x6,0x6,0x2,0x3,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};

// ITESM logo

static uint8_t ITESM_LOGO_ROWS = 8;
static uint8_t ITESM_LOGO_COLS = 60;
static const char ITESM_LOGO[] =
{
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0x80,0x80,0xc0,0xc0,0xc0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0x60,0xe0,0xe0,0xe0,0xe0,0xe0,0xc0,0xc0,0xc0,0x80,0x80,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xc0,0xc0,0xf0,0xf0,0xf8,0xfc,0xfc,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x3f,0x1f,0x7,0x1,0x0,0x80,0xe3,0xff,0x7f,0x3f,0xf,0x3,0x1,0x83,0xff,0xff,0xff,0xff,0xfe,0xfe,0xfc,0xf8,0xf0,0xf0,0xc0,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0xc0,0xf0,0xf8,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x3f,0x1f,0xf,0x7,0x3,0x81,0xc0,0xe0,0x70,0x38,0x1c,0xe,0x7,0x3,0x81,0xc0,0xe0,0xf0,0x38,0x3c,0xe,0x7,0x3,0x80,0xe1,0xff,0xff,0x7f,0x1f,0xf,0x7,0xff,0xff,0xff,0xff,0xfe,0xfc,0xf0,0xc0,0x0,0x0,0x0,
0x0,0xf0,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0xf,0x7,0x3,0x81,0xc0,0xe0,0x70,0x38,0xc,0xe,0x3,0x3,0x80,0xc0,0xe0,0xf0,0x38,0x3c,0xe,0xf,0x3,0x3,0xc0,0xc0,0xf0,0x70,0x3c,0x1c,0xf,0x7,0x3,0x81,0xc0,0xe0,0x70,0x38,0x3e,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0x0,
0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0x0,0xf8,0xfe,0xdf,0x3,0x0,0xc0,0xe0,0xf8,0x3c,0xe,0x7,0x3,0x1,0xc0,0xc0,0xf0,0x70,0x3c,0x1c,0xf,0x7,0x3,0x81,0xc0,0xe0,0x70,0x38,0x1c,0xe,0x7,0x3,0x81,0xc0,0xe0,0xf0,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,
0x0,0x0,0xf,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xff,0xff,0xfe,0xfe,0xff,0xff,0x0,0x0,0x0,0xf8,0xfe,0xff,0xff,0x3,0x0,0x0,0xe0,0xf0,0xfc,0xfe,0xff,0x7,0x1,0x80,0xc0,0xf0,0xf8,0xfc,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0xf,0x1,0x0,
0x0,0x0,0x0,0x0,0x0,0x3,0xf,0xf,0x3f,0x3f,0xff,0xff,0xff,0xff,0xcf,0xcf,0x8f,0xf,0xf,0xf,0xf,0xc,0xc,0xf,0xf,0xf,0xf,0xf,0xc,0xf,0xf,0xf,0xf,0xf,0xf,0xc,0xe,0xf,0xf,0xf,0xf,0xf,0xf,0xf,0xcf,0xcf,0xff,0xff,0xff,0xff,0x7f,0x3f,0xf,0xf,0x3,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3,0x3,0x7,0x7,0xf,0xf,0x1e,0x1e,0x3c,0x3c,0x3c,0x7c,0x78,0x78,0x30,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x78,0x78,0x78,0x3c,0x3c,0x3c,0x1e,0x1e,0xf,0xf,0x7,0x7,0x3,0x3,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};

// Linux logo

static uint8_t LINUX_LOGO_ROWS = 8;
static uint8_t LINUX_LOGO_COLS = 60;
static const char LINUX_LOGO[] =
{
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0xc0,0xe0,0xe0,0xe0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xe0,0xe0,0xe0,0xc0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf8,0x7f,0x1f,0x9f,0x1f,0x3f,0x7f,0xff,0xff,0x3f,0x1f,0x8f,0x8f,0x8f,0x1f,0x3f,0xff,0xff,0xff,0xff,0xfc,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0xfe,0x98,0xab,0xa7,0x24,0x4e,0x4b,0x43,0x42,0x4a,0x6f,0x27,0x27,0xac,0xdc,0x7f,0xff,0xff,0xff,0xff,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xc0,0xe0,0xf0,0xf8,0xfc,0x7f,0x1f,0x7,0x0,0x0,0x1,0x1,0x2,0x2,0x2,0x2,0x3,0x1,0x1,0x1,0x1,0x0,0x0,0x3,0xf,0x3f,0xff,0xff,0xff,0x7e,0xfc,0xf8,0xf0,0xe0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xc0,0xf0,0xf8,0x7e,0xf,0xf3,0xfd,0x1f,0x7,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3,0xf,0x3f,0xfc,0xfb,0x7,0x3f,0xff,0xff,0xfe,0xf8,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0x40,0x3c,0x1f,0x1f,0x1f,0x1c,0x30,0x67,0xc0,0xc0,0x80,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x60,0x20,0x10,0x7c,0xfd,0xfd,0xfc,0xf9,0xfb,0x73,0x27,0x2f,0x7f,0x46,0x80,0x0,0x0,0x0,0x0,
0x0,0x0,0xfc,0x2,0x1,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x3,0xf,0x1f,0x3f,0x7e,0x9c,0x10,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xc0,0x3f,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xe,0x18,0xb0,0x0,
0x0,0x0,0xf,0x8,0x0,0x10,0x10,0x10,0x10,0x10,0x10,0x0,0x20,0x20,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x21,0x1b,0x1e,0x1e,0xc,0xc,0xc,0xc,0xc,0xc,0xc,0xc,0xe,0xe,0xe,0xf,0x1f,0x21,0x40,0x80,0x80,0x80,0x80,0x80,0x40,0x40,0x20,0x30,0x10,0x8,0x4,0x4,0x2,0x2,0x0,0x1,0x0,0x0
};

// STM32 logo

static uint8_t STM32_LOGO_ROWS = 8;
static uint8_t STM32_LOGO_COLS = 60;
static const char STM32_LOGO[] =
{
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0x80,0x80,0xc0,0xc0,0xe0,0xe0,0xe0,0xe0,0xe0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xe0,0xe0,0xe0,0xe0,0xe0,0xc0,0xc0,0xc0,0x80,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0xc0,0xe0,0xf8,0xf8,0xfc,0xfe,0xfe,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x3f,0xf,0x7,0x3,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0x80,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x80,0xf0,0xf8,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0xe0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x3,0x3,0x7,0x0,0x1,0x3,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x20,0x38,0x7e,0xff,0xff,0xff,0xfc,0xf8,0xe0,0x0,0x0,
0xc0,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfc,0xf8,0xf8,0x30,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0x0,0x80,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x87,0xff,0xff,0xff,0xff,0xf8,
0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf1,0xc0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0xc0,0xe0,0xfc,0xff,0xfc,0xf0,0xff,0xfe,0xfc,0xfc,0xf8,0xf8,0xf0,0xf0,0xf0,0xf0,0xf8,0xfc,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0x0,0x7,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x1f,0xf,0xcf,0x8f,0x9f,0xff,0xdf,0xdf,0x1f,0x1f,0xdf,0xdf,0xff,0x1f,0x1f,0x1f,0xff,0xff,0x1f,0x1f,0x1f,0xff,0xbf,0x9f,0xcf,0xdf,0x1f,0xff,0xbf,0x9f,0xcf,0xdf,0x1f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x1f,0x1,
0x0,0x0,0x0,0x0,0x3,0x7,0x1f,0x3f,0x7f,0xf7,0xc6,0xcc,0xcc,0xc9,0xc1,0xf3,0xff,0xff,0xc0,0xc0,0xff,0xff,0xff,0xc0,0xfc,0xf8,0xc1,0xc0,0xfc,0xc0,0xc0,0xff,0xe7,0xcf,0xdc,0xdc,0xe1,0xff,0xcf,0xc7,0xdb,0xdd,0xdc,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x1f,0xf,0x7,0x1,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x3,0x7,0x7,0xf,0xf,0x1f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x1f,0x1f,0xf,0xf,0x7,0x3,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};

// Raspberry Pi logo

static uint8_t RASPBERRY_PI_LOGO_ROWS = 8;
static uint8_t RASPBERRY_PI_LOGO_COLS = 60;
static const char RASPBERRY_PI_LOGO[] =
{
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0x80,0xc0,0xc0,0xc0,0xe0,0xe0,0xe0,0xe0,0xe0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xc0,0xc0,0x80,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0xc0,0xf0,0xf0,0xf8,0xfc,0xfe,0xff,0xff,0x7f,0x7f,0x7f,0x3f,0xbf,0xbf,0xbf,0xbf,0xbf,0x3f,0x7f,0x7f,0xff,0xff,0xff,0xff,0x7f,0x7f,0x3f,0xbf,0xbf,0xbf,0xbf,0xbf,0x3f,0x7f,0x7f,0x7f,0xff,0xff,0xfe,0xfc,0xfc,0xf8,0xf0,0xe0,0xc0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x80,0xe0,0xf8,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xc3,0x1f,0x3f,0x7f,0xff,0xff,0xff,0xf7,0xef,0xdf,0x1e,0x1c,0x1,0x1,0x1c,0x1e,0x5f,0xef,0xff,0xf7,0xff,0xff,0xff,0x7f,0x3f,0x8f,0xe0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfc,0xf0,0xc0,0x0,0x0,
0x0,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x1f,0xf,0x73,0x78,0x38,0x9d,0x8d,0xc5,0xc1,0x98,0x9c,0x3e,0x3e,0x3e,0x3e,0x9c,0x9c,0xc0,0xc5,0xcd,0x9d,0x3c,0x38,0x72,0x7,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xc0,
0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3,0xf8,0xfc,0xfe,0x0,0x0,0x3f,0x7f,0x7f,0xff,0xff,0x7f,0x3f,0x9f,0x80,0x80,0x8e,0x3f,0x7f,0x7f,0xff,0xff,0x7f,0x3f,0x1e,0x0,0x3c,0xfe,0xfc,0x31,0x87,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,
0x0,0x3,0x1f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xf8,0xc1,0x1c,0x7e,0xfe,0xfc,0xfc,0xf8,0xe0,0x0,0x3e,0x3f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3e,0xc,0xc0,0xf0,0xf8,0xfc,0xfe,0x7e,0x3e,0x80,0xf0,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0x7,0x0,
0x0,0x0,0x0,0x0,0x1,0x7,0xf,0x1f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfe,0xfc,0xf9,0xf9,0xf0,0xe0,0xee,0xce,0xde,0xde,0xde,0xde,0xce,0xee,0xe4,0xf0,0xf9,0xf9,0xfd,0xfc,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x3f,0xf,0x7,0x3,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x3,0x7,0xf,0xf,0x1f,0x1f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x1f,0x1f,0xf,0xf,0x7,0x3,0x3,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};

#endif /* OLED_H_ */
