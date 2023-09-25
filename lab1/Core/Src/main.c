/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
void writePin(int ptr, int state){
	if (ptr == 12) ptr = 0;
	if (state == 0){
		if (ptr == 0) HAL_GPIO_WritePin(led12_GPIO_Port, led12_Pin, GPIO_PIN_SET);
		else if (ptr == 1) HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_SET);
		else if (ptr == 2) HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_SET);
		else if (ptr == 3) HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_SET);
		else if (ptr == 4) HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_SET);
		else if (ptr == 5) HAL_GPIO_WritePin(led5_GPIO_Port, led5_Pin, GPIO_PIN_SET);
		else if (ptr == 6) HAL_GPIO_WritePin(led6_GPIO_Port, led6_Pin, GPIO_PIN_SET);
		else if (ptr == 7) HAL_GPIO_WritePin(led7_GPIO_Port, led7_Pin, GPIO_PIN_SET);
		else if (ptr == 8) HAL_GPIO_WritePin(led8_GPIO_Port, led8_Pin, GPIO_PIN_SET);
		else if (ptr == 9) HAL_GPIO_WritePin(led9_GPIO_Port, led9_Pin, GPIO_PIN_SET);
		else if (ptr == 10) HAL_GPIO_WritePin(led10_GPIO_Port, led10_Pin, GPIO_PIN_SET);
		else if (ptr == 11) HAL_GPIO_WritePin(led11_GPIO_Port, led11_Pin, GPIO_PIN_SET);
	}else{
		if (ptr == 0) HAL_GPIO_WritePin(led12_GPIO_Port, led12_Pin, GPIO_PIN_RESET);
		else if (ptr == 1) HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_RESET);
		else if (ptr == 2) HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_RESET);
		else if (ptr == 3) HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_RESET);
		else if (ptr == 4) HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_RESET);
		else if (ptr == 5) HAL_GPIO_WritePin(led5_GPIO_Port, led5_Pin, GPIO_PIN_RESET);
		else if (ptr == 6) HAL_GPIO_WritePin(led6_GPIO_Port, led6_Pin, GPIO_PIN_RESET);
		else if (ptr == 7) HAL_GPIO_WritePin(led7_GPIO_Port, led7_Pin, GPIO_PIN_RESET);
		else if (ptr == 8) HAL_GPIO_WritePin(led8_GPIO_Port, led8_Pin, GPIO_PIN_RESET);
		else if (ptr == 9) HAL_GPIO_WritePin(led9_GPIO_Port, led9_Pin, GPIO_PIN_RESET);
		else if (ptr == 10) HAL_GPIO_WritePin(led10_GPIO_Port, led10_Pin, GPIO_PIN_RESET);
		else if (ptr == 11) HAL_GPIO_WritePin(led11_GPIO_Port, led11_Pin, GPIO_PIN_RESET);
	}
}
void clearAllClock(){
	for (int i = 0; i < 11; i++){
		writePin(i, 0);
	}
}

void setNumberOnClock(int num){
	if (num >= 0 && num <= 11) writePin(num, 1);
}

void clearNumberOnClock(int num){
	if (num >= 0 && num <= 11) writePin(num, 0);
}
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

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
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */
  int sec = 0, min = 0, hr = 0;
  int led_sec[12] = {0};
  int led_min[12] = {0};
  int led_hr[12] = {0};
  led_sec[0] = 1;
  led_min[0] = 1;
  led_hr[0] = 1;
  int curr = 0, prev = 11;
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	if (sec%5 == 0){
		if (sec >= 60 || sec == 0){
			curr = 0;
			prev = 11;
		}
		else {
			curr = sec/5;
			prev = curr-1;
		}
		led_sec[curr] = 1;
		led_sec[prev] = 0;
		writePin(prev, led_sec[prev] | led_min[prev] | led_hr[prev]);
		writePin(curr, 1);
		if (sec >= 60){
			sec = 0;
			min++;
			if (min%5 == 0){
				if (min >= 60 || min == 0){
					curr = 0;
					prev = 11;
				}
				else{
					curr = min/5;
					prev = curr-1;
				}
				led_min[curr] = 1;
				led_min[prev] = 0;
				writePin(prev, led_sec[prev] | led_min[prev] | led_hr[prev]);
				writePin(curr, 1);

				if (min >= 60){
					min = 0;
					hr++;
					if (hr >= 12){
						led_hr[0] = 1;
						led_hr[11] = 0;
						writePin(0, 1);
						writePin(11, led_hr[11] + led_min[11] + led_sec[11]);
						hr = 0;
					}else{
						led_hr[hr] = 1;
						led_hr[hr-1] = 0;
						writePin(hr, 1);
						writePin(hr-1, led_hr[hr-1] + led_min[hr-1] + led_sec[hr-1]);
					}
				}
			}
		}
	}sec++;
	HAL_Delay(1000);
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, led1_Pin|led2_Pin|led3_Pin|led4_Pin
                          |led5_Pin|led6_Pin|led7_Pin|led8_Pin
                          |led9_Pin|led10_Pin|led11_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(led12_GPIO_Port, led12_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : led1_Pin led2_Pin led3_Pin led4_Pin
                           led5_Pin led6_Pin led7_Pin led8_Pin
                           led9_Pin led10_Pin led11_Pin led12_Pin */
  GPIO_InitStruct.Pin = led1_Pin|led2_Pin|led3_Pin|led4_Pin
                          |led5_Pin|led6_Pin|led7_Pin|led8_Pin
                          |led9_Pin|led10_Pin|led11_Pin|led12_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
