/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "libraries.h"
#include "main.h"
#include "GPIO.h"
#include "TIMER.h"
#include "ADC.h"
#include "UART.h"
#include "I2C.h"
#include "MATRIX_KEYPAD.h"
#include "LCD.h"
#include "LEDS.h"
#include "OLED.h"
#include "PWM.h"

/* Model's header file */

#include "EngTrModel.h"
#include "rtwtypes.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define STACK_SIZE	128

#define PERIOD_TASK_1	12
#define PERIOD_TASK_2	9
#define PERIOD_TASK_3	3
#define PERIOD_TASK_4	6
#define PERIOD_TASK_5	1
#define PERIOD_TASK_6	1
#define PERIOD_TASK_7	1
#define PERIOD_TASK_8	1

#define TICK_DIFF_TASK_1	(osKernelSysTick() - (PERIOD_TASK_1 * counter++))
#define TICK_DIFF_TASK_2	(osKernelSysTick() - (PERIOD_TASK_2 * counter++))
#define TICK_DIFF_TASK_3	(osKernelSysTick() - (PERIOD_TASK_2 * counter++))
#define TICK_DIFF_TASK_4	(osKernelSysTick() - (PERIOD_TASK_4 * counter++))
#define TICK_DIFF_TASK_5	(osKernelSysTick() - (PERIOD_TASK_5 * counter++))
#define TICK_DIFF_TASK_6	(osKernelSysTick() - (PERIOD_TASK_6 * counter++))
#define TICK_DIFF_TASK_7	(osKernelSysTick() - (PERIOD_TASK_7 * counter++))
#define TICK_DIFF_TASK_8	(osKernelSysTick() - (PERIOD_TASK_8 * counter++))

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

UART_HandleTypeDef huart2;
osThreadId defaultTaskHandle;

/* USER CODE BEGIN PV */

// RTOS

osThreadId Task1Handle;
osThreadId Task2Handle;
osThreadId Task3Handle;
osThreadId Task4Handle;
osThreadId Task5Handle;
osThreadId Task6Handle;
osThreadId Task7Handle;
osThreadId Task8Handle;

osMutexId Mutex1Handle;

// Matrix keypad

char selectedKey = 'N';
float keyBrakeTorque = 0.0;

// ADC

uint16_t conversionData = 0;
float voltageValue = 0.0, potentiometerThrottle = 0.0;

// UART

uint8_t receivedThrottle = 0;

// Mode select

uint8_t operationMode = 0;

// Data format

int ThrottleWhole = 0;
int ThrottleDecimal = 0;

int VehicleSpeedWhole = 0;
int VehicleSpeedDecimal = 0;

int EngineSpeedWhole = 0;
int EngineSpeedDecimal = 0;

int BrakeWhole = 0;
int GearWhole = 0;

// LCD

char FirstLine_LCD_MSG[LCD_CHARS + 1];
char SecondLine_LCD_MSG[LCD_CHARS + 1];

// OLED

char oled_buffer[OLED_SCREEN_ROWS][OLED_SCREEN_COLUMNS];
char OLED_MSGS[OLED_MSGS_NUMBER][OLED_SCREEN_COLUMNS];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
void StartDefaultTask(void const * argument);

/* USER CODE BEGIN PFP */

void TASK_1_MATRIX_KEYPAD_Read(void const * argument);
void TASK_2_ADC_Read( void const * argument );
void TASK_3_UART_Read( void const * argument );
void TASK_4_MODEL_Step( void const * argument );
void TASK_5_UART_Send( void const * argument );
void TASK_6_DATA_Format( void const * argument );
void TASK_7_LCD_Write( void const * argument );
void TASK_8_OLED_Write( void const * argument );

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */

  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */

  MX_GPIO_Init();
  MX_USART2_UART_Init();

  /* USER CODE BEGIN 2 */

  USER_OLED_Init_64( I2C_2 );
  //USER_OLED_Animation( I2C_2, oled_buffer );

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */

  osMutexDef(Mutex1);
  Mutex1Handle = osMutexCreate(osMutex(Mutex1));

  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */

  /* USER CODE BEGIN RTOS_THREADS */

  osThreadDef(Task2, TASK_2_ADC_Read, osPriorityAboveNormal, 0, STACK_SIZE);
  Task2Handle = osThreadCreate(osThread(Task2), NULL);

  osThreadDef(Task4, TASK_4_MODEL_Step, osPriorityNormal, 0, STACK_SIZE);
  Task4Handle = osThreadCreate(osThread(Task4), NULL);

  osThreadDef(Task3, TASK_3_UART_Read, osPriorityRealtime, 0, STACK_SIZE);
  Task3Handle = osThreadCreate(osThread(Task3), NULL);

  osThreadDef(Task1, TASK_1_MATRIX_KEYPAD_Read, osPriorityBelowNormal, 0, STACK_SIZE);
  Task1Handle = osThreadCreate(osThread(Task1), NULL);

  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */

  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

// Tasks

/* Read the matrix keyboard and
 * adapt the brake value, LEDs states,
 * micro servo direction and operation mode
 * based on the selected key.
 */

void TASK_1_MATRIX_KEYPAD_Read( void const * argument )
{
  USER_USART_Init( USART_1 );
  EngTrModel_initialize();

  USER_MATRIX_KEYPAD_Init();
  USER_LEDS_Init();
  USER_PWM_Init();

  uint32_t counter = 0;

  /* Infinite loop */

  for(;;)
  {
    printf("T1 DEBUG\r\n");

    selectedKey = USER_MATRIX_KEYPAD_Read();

    if(selectedKey == '5')							// Brake action
    {
      keyBrakeTorque = 100.0;							// Full brake torque

      USER_TIM_Delay( TIM_3, TIM_PSC_200MS, TIM_CNT_200MS );			// LEDs blinking
    }
    else if(selectedKey == '4' || selectedKey == '6')				// Left or right action
    {
      keyBrakeTorque = 50.0;							// Half brake torque

      if(selectedKey == '4')							// Left action
      {
	USER_GPIO_Write( PORTC, 2, 1 );						// Left LED turned on
	USER_PWM_Generate( PWM_PSC_20MS, PWM_ARR_20MS, PWM_CCRX_12_5 );		// The micro servo rotates to a 180° position
      }
      else									// Right action
      {
	USER_GPIO_Write( PORTC, 3, 1 );						// Right LED turned on
	USER_PWM_Generate( PWM_PSC_20MS, PWM_ARR_20MS, PWM_CCRX_2_5 );		// The micro servo rotates to a 0° position
      }
    }
    else if(selectedKey == 'A')							// Select manual mode action
    {
      operationMode = 0;							// Manual mode
    }
    else if(selectedKey == 'B')							// Select simulation mode action
    {
      operationMode = 1;							// Simulation mode
    }
    else									// No action
    {
      keyBrakeTorque = 0.0;							// No brake torque

      USER_GPIO_Write( PORTC, 2, 0 );						// LEDs turned off
      USER_GPIO_Write( PORTC, 3, 0 );
    }

    osDelay(PERIOD_TASK_1 - TICK_DIFF_TASK_1);
  }
}

/* Read the ADC conversion, convert it to a voltage value,
 * and normalize it to within the range accepted by the model,
 * this for manual mode.
 */

void TASK_2_ADC_Read( void const * argument )
{
  USER_ADC_Init( ADC_1 );

  uint32_t counter = 0;

  /* Infinite loop */

  for(;;)
  {
    printf("T2 DEBUG\r\n");

    conversionData = USER_ADC_Convert( ADC_1 );
    voltageValue = 0.00080586 * conversionData;
    potentiometerThrottle = scaleVoltageValue( voltageValue, 0, 3.3 );

    osDelay(PERIOD_TASK_2 - TICK_DIFF_TASK_2);
  }
}

/* Read the throttle value sent via UART by the Raspeberry Pi
 * for simulation mode.
 */

void TASK_3_UART_Read( void const * argument )
{
  uint32_t counter = 0;

  /* Infinite loop */

  for(;;)
  {
    printf("T3 DEBUG\r\n");

    if( USART1->SR & USART_SR_RXNE )						// If USART_DR is not empty
    {
	receivedThrottle = USART1->DR;						// Receive data
    }

    osDelay(PERIOD_TASK_3 - TICK_DIFF_TASK_3);
  }
}

/* Feed the model with the throttle value
 * and the brake value, take a step and
 * sanitize the output values.
 */

void TASK_4_MODEL_Step( void const * argument )
{
  uint32_t counter = 0;

  /* Infinite loop */

  for(;;)
  {
    printf("T4 DEBUG\r\n");

    if(operationMode == 0)							// Manual mode
    {
      EngTrModel_U.Throttle = potentiometerThrottle;				// Model feed with potentiometer throttle value
    }
    else									// Simulation mode
    {
      EngTrModel_U.Throttle = (float) receivedThrottle;				// Model feed with received throttle value
    }

    EngTrModel_U.BrakeTorque = keyBrakeTorque;					// Model feed with brake value

    EngTrModel_step();								// Take a step

    // Sanitize the output values

    if(isnan(EngTrModel_Y.VehicleSpeed) || EngTrModel_Y.VehicleSpeed < 0 || EngTrModel_Y.VehicleSpeed > 200)
    {
      EngTrModel_Y.VehicleSpeed = 0.0;
    }

    if(isnan(EngTrModel_Y.EngineSpeed) || EngTrModel_Y.EngineSpeed < 0)
    {
      EngTrModel_Y.EngineSpeed = 0.0;
    }

    if(isnan(EngTrModel_Y.Gear) || EngTrModel_Y.Gear < 0)
    {
      EngTrModel_Y.Gear = 0.0;
    }

    osDelay(PERIOD_TASK_4 - TICK_DIFF_TASK_4);
  }
}

/* Send via UART the output values of the model,
 * subsequently received by the Raspberry Pi.
 */

void TASK_5_UART_Send( void const * argument )
{
  uint32_t counter = 0;

  /* Infinite loop */

  for(;;)
  {
    printf("T5 DEBUG\r\n");

    printf("%f,%f,%f,%f,%f\n\r", potentiometerThrottle, keyBrakeTorque, EngTrModel_Y.VehicleSpeed, EngTrModel_Y.EngineSpeed, EngTrModel_Y.Gear);

    osDelay(PERIOD_TASK_5 - TICK_DIFF_TASK_5);
  }
}

/* Extract the whole and decimal parts for Throttle,
 * Engine Speed and Vehicle Speed, and cast them
 * alongside Brake and Gear to integers.
 */

void TASK_6_DATA_Format( void const * argument )
{
  uint32_t counter = 0;

  /* Infinite loop */

  for(;;)
  {
    printf("T6 DEBUG\r\n");

    ThrottleWhole = (int) ( potentiometerThrottle );
    ThrottleDecimal = (int) ( ( potentiometerThrottle - ThrottleWhole ) * 100 );

    VehicleSpeedWhole = (int)( EngTrModel_Y.VehicleSpeed );
    VehicleSpeedDecimal = (int)( ( EngTrModel_Y.VehicleSpeed - VehicleSpeedWhole ) * 100 );

    EngineSpeedWhole = (int)( EngTrModel_Y.EngineSpeed );
    EngineSpeedDecimal = (int)( ( EngTrModel_Y.EngineSpeed - EngineSpeedWhole ) * 100 );

    BrakeWhole = (int) ( keyBrakeTorque );
    GearWhole = (int) ( EngTrModel_Y.Gear );

    osDelay(PERIOD_TASK_6 - TICK_DIFF_TASK_6);
  }
}

/* Properly format the model output data
 * and display it on the LCD
 */

void TASK_7_LCD_Write( void const * argument )
{
  USER_TIM_Init( TIM_2 );
  USER_LCD_Init();

  uint32_t counter = 0;

  /* Infinite loop */

  for(;;)
  {
    printf("T7 DEBUG\r\n");

    // Write the messages to send to the LCD

    snprintf( FirstLine_LCD_MSG, sizeof(FirstLine_LCD_MSG), "%03d.%01d  %03d.%01d m/s", ThrottleWhole, ThrottleDecimal / 10, VehicleSpeedWhole, VehicleSpeedDecimal / 10 );
    snprintf( SecondLine_LCD_MSG, sizeof(SecondLine_LCD_MSG), "%03d %01d %04d.%01d RPM", BrakeWhole, GearWhole, EngineSpeedWhole, EngineSpeedDecimal / 10 );

    // Display values on the LCD

    LCD_Set_Cursor( 1, 1 );
    LCD_Put_Str( FirstLine_LCD_MSG );
    LCD_Set_Cursor( 2, 1 );
    LCD_Put_Str( SecondLine_LCD_MSG );

    osDelay(PERIOD_TASK_7 - TICK_DIFF_TASK_7);
  }
}

/* Display the output model data
 *  on the OLED screen.
 */

void TASK_8_OLED_Write( void const * argument )
{
  uint32_t counter = 0;

  /* Infinite loop */

  for(;;)
  {
    printf("T8 DEBUG\r\n");

    // Write the messages to send to the OLED screen

     if(operationMode == 0)								// Manuel mode
     {
       snprintf(OLED_MSGS[0], sizeof(OLED_MSGS[0]), "MODE: Man");
     }
     else										// Simulation mode
     {
       snprintf(OLED_MSGS[0], sizeof(OLED_MSGS[0]), "MODE: Sim");
     }

     snprintf(OLED_MSGS[1], sizeof(OLED_MSGS[1]), "MANUAL THROTTLE: %03d.%02d", ThrottleWhole, ThrottleDecimal);
     snprintf(OLED_MSGS[2], sizeof(OLED_MSGS[2]), "SIMULATION THROTTLE: %03d", receivedThrottle);
     snprintf(OLED_MSGS[3], sizeof(OLED_MSGS[3]), "BRAKE: %03d", BrakeWhole);
     snprintf(OLED_MSGS[4], sizeof(OLED_MSGS[4]), "VEHICLE SPEED: %03d.%02d m/s", VehicleSpeedWhole, VehicleSpeedDecimal);
     snprintf(OLED_MSGS[5], sizeof(OLED_MSGS[5]), "ENGINE SPEED: %04d.%02d RPM", EngineSpeedWhole, EngineSpeedDecimal);
     snprintf(OLED_MSGS[6], sizeof(OLED_MSGS[6]), "GEAR: %01d", GearWhole);

     // Display values on the OLED screen

     for (int i = 0; i < OLED_MSGS_NUMBER; ++i)
     {
       USER_OLED_Message( I2C_2, OLED_MSGS[i], 0, i );
     }

     osDelay(PERIOD_TASK_8 - TICK_DIFF_TASK_8);
  }
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
      printf("Default\r\n");
      osDelay(2000);
  }
  /* USER CODE END 5 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
