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

/* Function prototypes */

void USER_RCC_ClockEnable( void );

/* Main function */

int main( void )
{
  EngTrModel_initialize();

  USER_RCC_ClockEnable();
  USER_TIM_Init( TIM_2 );
  USER_ADC_Init( ADC_1 );
  USER_USART_Init( USART_1 );
  USER_LCD_Init();
  USER_MATRIX_KEYPAD_Init();
  USER_SYSTICK_Init();
  USER_OLED_Init_64( I2C_2 );

  USER_OLED_Animation( I2C_2, oled_buffer );

  /* Loop forever */

  for(;;)
  {
    // ADC

    conversionData = USER_ADC_Convert( ADC_1 );
    voltageValue = 0.00080586 * conversionData;

    // Matrix keypad

    selectedKey = USER_MATRIX_KEYPAD_Read();

    // printf("%f_%c\n\r", voltageValue, selectedKey);			// Debug ADC and matrix keypad

    if(selectedKey == '5')
    {
      keyBrakeTorque = 100.0;
      action = 'B';
    }
    else if(selectedKey == '4' || selectedKey == '6')
    {
      voltageValue -= 1;

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

    normalizedVoltageValue = scaleVoltageValue( voltageValue, 0, 3.3 );

    // printf("%f_%f\n\r", normalizedVoltageValue, keyBrakeTorque);	// Debug normalizedVoltageValue and keyBrakeTorque

    // Update the values for the Throttle and Brake commands

    EngTrModel_U.Throttle = normalizedVoltageValue;
    EngTrModel_U.BrakeTorque = keyBrakeTorque;

    // Update the values into the vehicle model

    EngTrModel_step();

    // Send the output values

    // printf("%f,%f,%f\n\r", EngTrModel_Y.EngineSpeed, EngTrModel_Y.VehicleSpeed, EngTrModel_Y.Gear);

    USER_TIM_Delay( TIM_2, TIM_PSC_40MS, TIM_CNT_40MS );		// 40 ms delay

    // Extract the whole and decimal parts for Engine Speed and Vehicle Speed, and cast them alongside Gear to integers

    int EngineSpeedWhole = (int)( EngTrModel_Y.EngineSpeed );
    int EngineSpeedDecimal = (int)( ( EngTrModel_Y.EngineSpeed - EngineSpeedWhole ) * 100 );

    int VehicleSpeedWhole = (int)( EngTrModel_Y.VehicleSpeed );
    int VehicleSpeedDecimal = (int)( ( EngTrModel_Y.VehicleSpeed - VehicleSpeedWhole ) * 100 );

    int GearWhole = (int) ( EngTrModel_Y.Gear );

    // Write the messages to send to the LCD

    snprintf( FirstLine_LCD_MSG, sizeof(FirstLine_LCD_MSG), "E:%04d.%02d G:%01d  %c", EngineSpeedWhole, EngineSpeedDecimal, GearWhole, action );
    snprintf( SecondLine_LCD_MSG, sizeof(SecondLine_LCD_MSG), "V:%03d.%02d        ", VehicleSpeedWhole, VehicleSpeedDecimal );

    // Display values on the LCD

    LCD_Set_Cursor( 1, 1 );
    LCD_Put_Str( FirstLine_LCD_MSG );
    LCD_Set_Cursor( 2, 1 );
    LCD_Put_Str( SecondLine_LCD_MSG );

    USER_TIM_Delay( TIM_2, TIM_PSC_200MS, TIM_CNT_200MS );		// 200 ms delay
  }

}

void USER_RCC_ClockEnable( void )
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
