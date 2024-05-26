/*
 * main.c
 */

/* Libraries, Definitions and Global Declarations */

#include "libraries.h"
#include "main.h"
#include "GPIO.h"
#include "timer.h"
#include "SYSTICK.h"
#include "ADC.h"
#include "uart.h"
#include "I2C.h"
#include "lcd.h"
#include "matrix_keypad.h"
#include "OLED.h"

// ADC

uint16_t conversionData = 0;
float voltageValue = 0, normalizedVoltageValue = 0;

// Matrix keypad

char selectedKey = 'N';
char action = 'F';
float keyBrakeTorque = 0;

// LCD

uint8_t col = 16;
char FirstLine_LCD_MSG[LCD_CHARS + 1];
char SecondLine_LCD_MSG[LCD_CHARS + 1];

// OLED

char oled_buffer[OLED_SCREEN_ROWS][OLED_SCREEN_COLUMNS];

// Time measuring

float time;
uint16_t start, end, total;

/* Function prototypes */

void USER_RCC_ClockEnable( void );
void USER_TIM4_Init_Timer( void );

void TASK_1_MATRIX_KEYPAD_Read_Init( void );
void TASK_2_ADC_Read_Init( void );
void TASK_3_MODEL_Feed_Init( void );
void TASK_4_USART_Send_Init( void );
void TASK_5_LCD_Write_Init( void );

void TASK_1_MATRIX_KEYPAD_Read( void );
void TASK_2_ADC_Read( void );
void TASK_3_MODEL_Feed( void );
void TASK_4_USART_Send( void );
void TASK_5_LCD_Write( void );

/* Main function */

int main( void )
{
  USER_TIM_Init( TIM_2 );
  USER_TIM4_Init_Timer();
  USER_USART_Init( USART_1 );

  /* Loop forever */

  for(;;)
  {
      TIM4->CNT = 0;
      start = TIM4->CNT;
      TASK_1_MATRIX_KEYPAD_Read_Init();
      end = TIM4->CNT;
      total = end - start;
      time = T_HCLK * total * ( TIM4->PSC + 1);
      printf("Matrix Init Time is: %f\r\n", time);
      USER_TIM_Delay( TIM_2, TIM_PSC_1S, TIM_CNT_1S );

      TIM4->CNT = 0;
      start = TIM4->CNT;
      TASK_1_MATRIX_KEYPAD_Read();
      end = TIM4->CNT;
      total = end - start;
      time = T_HCLK * total * ( TIM4->PSC + 1);
      printf("Matrix Read Time is: %f\r\n", time);
      USER_TIM_Delay( TIM_2, TIM_PSC_1S, TIM_CNT_1S );

      TIM4->CNT = 0;
      start = TIM4->CNT;
      TASK_2_ADC_Read_Init();
      end = TIM4->CNT;
      total = end - start;
      time = T_HCLK * total * ( TIM4->PSC + 1);
      printf("ADC Init Time is: %f\r\n", time);
      USER_TIM_Delay( TIM_2, TIM_PSC_1S, TIM_CNT_1S );

      TIM4->CNT = 0;
      start = TIM4->CNT;
      TASK_2_ADC_Read();
      end = TIM4->CNT;
      total = end - start;
      time = T_HCLK * total * ( TIM4->PSC + 1);
      printf("ADC Read Time is: %f\r\n", time);
      USER_TIM_Delay( TIM_2, TIM_PSC_1S, TIM_CNT_1S );

      TIM4->CNT = 0;
      start = TIM4->CNT;
      TASK_3_MODEL_Feed_Init();
      end = TIM4->CNT;
      total = end - start;
      time = T_HCLK * total * ( TIM4->PSC + 1);
      printf("Model Init Time is: %f\r\n", time);
      USER_TIM_Delay( TIM_2, TIM_PSC_1S, TIM_CNT_1S );

      TIM4->CNT = 0;
      start = TIM4->CNT;
      TASK_3_MODEL_Feed();
      end = TIM4->CNT;
      total = end - start;
      time = T_HCLK * total * ( TIM4->PSC + 1);
      printf("Model Feed Time is: %f\r\n", time);
      USER_TIM_Delay( TIM_2, TIM_PSC_1S, TIM_CNT_1S );

      TIM4->CNT = 0;
      start = TIM4->CNT;
      TASK_4_USART_Send_Init();
      end = TIM4->CNT;
      total = end - start;
      time = T_HCLK * total * ( TIM4->PSC + 1);
      printf("USART Init Time is: %f\r\n", time);
      USER_TIM_Delay( TIM_2, TIM_PSC_1S, TIM_CNT_1S );

      TIM4->CNT = 0;
      start = TIM4->CNT;
      TASK_4_USART_Send();
      end = TIM4->CNT;
      total = end - start;
      time = T_HCLK * total * ( TIM4->PSC + 1);
      printf("USART Send Time is: %f\r\n", time);
      USER_TIM_Delay( TIM_2, TIM_PSC_1S, TIM_CNT_1S );

      TIM4->CNT = 0;
      start = TIM4->CNT;
      TASK_5_LCD_Write_Init();
      end = TIM4->CNT;
      total = end - start;
      time = T_HCLK * total * ( TIM4->PSC + 1);
      printf("LCD Init Time is: %f\r\n", time);
      USER_TIM_Delay( TIM_2, TIM_PSC_1S, TIM_CNT_1S );

      TIM4->CNT = 0;
      start = TIM4->CNT;
      TASK_5_LCD_Write();
      end = TIM4->CNT;
      total = end - start;
      time = T_HCLK * total * ( TIM4->PSC + 1);
      printf("LCD Write Time is: %f\r\n", time);
      USER_TIM_Delay( TIM_2, TIM_PSC_1S, TIM_CNT_1S );
  }

}

void USER_RCC_Init( void )
{
  /* System Clock (SYSCLK) configuration for 64 MHz */

  // Two wait states latency, if SYSCLK > 48 MHz

  FLASH->ACR	&=	~( 0x5UL << 0U );	
  FLASH->ACR	|=	( 0x2UL << 0U );	
  
  // PLL HSI clock /2 selected as PLL input clock
  
  RCC->CFGR	&=	~( 0x1UL << 16U )
		&	~( 0x7UL << 11U )	// APB2 pre-scaler /1
		&	~( 0x3UL << 8U )        // APB1 pre-scaler /2 (APB1 must not exceed 36 MHz)
		&	~( 0xFUL << 4U );	// AHB pre-scaler /1

  // PLL input clock x 16 (PLLMUL bits)

  RCC->CFGR	|=	( 0xFUL << 18U )	
		|	( 0X4UL << 8U );	// APB1 pre-scaler /2
  RCC->CR	|=	( 0x1UL << 24U );	// PLL2 ON

  // Wait until PLL is locked

  while( !(RCC->CR & ~( 0x1UL << 25U )));

  // PLL used as system clock (SW bits)

  RCC->CFGR	&=	~( 0x1UL << 0U );
  RCC->CFGR	|=	( 0x2UL << 0U );

  // Wait until PLL is switched

  while( 0x8UL != ( RCC->CFGR & 0xCUL ));
}

void USER_TIM4_Init_Timer( void ){
    RCC->APB1ENR	|=	RCC_APB1ENR_TIM4EN;
    TIM4->SMCR &=  ~( 0x7UL <<  0U );
    TIM4->CR1  &=  ~( 0x3UL <<  5U )
               &   ~( 0x1UL <<  4U )
               &   ~( 0x1UL <<  1U );
    TIM4->PSC   =    0;
    TIM4->EGR  |=   ( 0x1UL <<  0U );
    TIM4->CNT   =    0;
    TIM4->SR   &=  ~( 0x1UL <<  0U );
    TIM4->CR1  |=   ( 0x1UL <<  0U );
}

void TASK_1_MATRIX_KEYPAD_Read_Init( void )
{
  USER_MATRIX_KEYPAD_Init();
  return;
}

void TASK_2_ADC_Read_Init( void )
{
  USER_RCC_Init();
  USER_TIM_Init( TIM_2 );
  USER_ADC_Init( ADC_1 );

  return;
}

void TASK_3_MODEL_Feed_Init( void )
{
  EngTrModel_initialize();
  return;
}

void TASK_4_USART_Send_Init( void )
{
  USER_USART_Init( USART_1 );
  return;
}

void TASK_5_LCD_Write_Init( void )
{
  USER_LCD_Init();
  return;
}

void TASK_1_MATRIX_KEYPAD_Read( void )
{
  selectedKey = USER_MATRIX_KEYPAD_Read();

  if(selectedKey == '5')
  {
    keyBrakeTorque = 100.0;
    action = 'B';
  }
  else if(selectedKey == '4' || selectedKey == '6')
  {
    keyBrakeTorque = 50.0;

    if(selectedKey == '4')
    {
	action = 'L';
    }
    else
    {
	action = 'R';
    }
  }
  else
  {
    keyBrakeTorque = 0.0;
    action = 'F';
  }

  return;
}

void TASK_2_ADC_Read( void )
{
  conversionData = USER_ADC_Convert( ADC_1 );
  voltageValue = 0.00080586 * conversionData;

  normalizedVoltageValue = scaleVoltageValue( voltageValue, 0, 3.3 );

  return;
}

void TASK_3_MODEL_Feed( void )
{
  EngTrModel_U.Throttle = normalizedVoltageValue;
  EngTrModel_U.BrakeTorque = keyBrakeTorque;

  EngTrModel_step();

  return;
}

void TASK_4_USART_Send( void )
{
  printf("%f,%f,%f\n\r", EngTrModel_Y.EngineSpeed, EngTrModel_Y.VehicleSpeed, EngTrModel_Y.Gear);

  return;
}

void TASK_5_LCD_Write( void )
{
  int EngineSpeedWhole = (int)( EngTrModel_Y.EngineSpeed );
  int EngineSpeedDecimal = (int)( ( EngTrModel_Y.EngineSpeed - EngineSpeedWhole ) * 100 );

  int VehicleSpeedWhole = (int)( EngTrModel_Y.VehicleSpeed );
  int VehicleSpeedDecimal = (int)( ( EngTrModel_Y.VehicleSpeed - VehicleSpeedWhole ) * 100 );

  int GearWhole = (int) ( EngTrModel_Y.Gear );

  snprintf( FirstLine_LCD_MSG, sizeof(FirstLine_LCD_MSG), "E:%04d.%02d G:%01d  %c", EngineSpeedWhole, EngineSpeedDecimal, GearWhole, action );
  snprintf( SecondLine_LCD_MSG, sizeof(SecondLine_LCD_MSG), "V:%03d.%02d        ", VehicleSpeedWhole, VehicleSpeedDecimal );

  LCD_Set_Cursor( 1, 1 );
  LCD_Put_Str( FirstLine_LCD_MSG );
  LCD_Set_Cursor( 2, 1 );
  LCD_Put_Str( SecondLine_LCD_MSG );

  return;
}
