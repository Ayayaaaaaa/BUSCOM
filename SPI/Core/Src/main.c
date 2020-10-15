/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include <stdio.h>
//#include "SX1278.h"
#include "SX1272.h"
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
SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

void SX1272_SPIBurstRead(uint8_t addr, uint8_t* rxBuf, uint8_t length) {
	uint8_t i;
	if (length <= 1) {
		return;
	} else {
		HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_RESET);
		HAL_SPI_Transmit(&hspi1, &addr, 1, 1000);
		HAL_SPI_Receive(&hspi1, rxBuf, length, 1000);
		HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_SET);
	}
}


uint8_t SPI_Read_Register(uint8_t reg){
		uint8_t data = 0;
		HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, 0);

		reg &= 0x7F;

		HAL_SPI_Transmit(&hspi1, &reg, 1, 1000);
		HAL_SPI_Receive(&hspi1, &data, 1, 1000);

		while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);

		HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, 1);
		return data;
}

uint8_t SX1272_Receive(uint8_t Rx[50]){
	uint8_t length = 0;
	uint8_t addr = SPI_Read_Register(0x0F);//Rx base addr
	SX1272_WriteRegister(0x0D, addr);//write fifo addr ptr

	HAL_Delay(15);
	SX1272_WriteRegister(0x01, 0x81);
	HAL_Delay(15);
	SX1272_WriteRegister(0x01, 0x84);
	HAL_Delay(15);
	SX1272_WriteRegister(0x01, 0x85);
	HAL_Delay(15);


	while((SPI_Read_Register(0x12) && 0xC0)==0);//interrupt

	uint8_t interrupt = SPI_Read_Register(0x12);
	if(interrupt == 0x80){
		return 0;
	}

	addr = SPI_Read_Register(0x10);//Rx current addr
	length = SPI_Read_Register(0x13);//Rx current addr

	SX1272_WriteRegister(0x0D, addr);//write fifo addr ptr

	SX1272_SPIBurstRead(0, Rx, length);
	SX1272_WriteRegister(0x12, 0xFF);//clear interrupt
	return length;

}

void SX1272_Transmit(uint8_t Tx){
	uint8_t addr = SPI_Read_Register(0x0E);//Tx base addr
	SX1272_WriteRegister(0x0D, addr);//write fifo addr ptr

	HAL_Delay(15);
	SX1272_WriteRegister(0x01, 0x81);
	HAL_Delay(15);
	SX1272_WriteRegister(0x00, Tx);
	HAL_Delay(15);
	SX1272_WriteRegister(0x01, 0x82);
	HAL_Delay(15);
	SX1272_WriteRegister(0x01, 0x83);
	HAL_Delay(15);


	while((SPI_Read_Register(0x12) && 0x08)==0);//interrupt

	uint8_t interrupt = SPI_Read_Register(0x12);

	SX1272_WriteRegister(0x12, 0xFF);//clear interrupt
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//! @last_edit : 10/07/2020
//! @details : PRINTF TO UART handling
int __io_putchar(int ch)
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USARTx and Loop until the end of transmission */
	while (HAL_OK != HAL_UART_Transmit(&huart2, (uint8_t *) &ch, 1, HAL_MAX_DELAY))
	{
		;
	}
	return ch;
}
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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  //define necessary structures
  /*SX1278_hw_t SX1278_hw;
  SX1278_t SX1278;
  int master = 1;
  int ret;
  char buffer[64];
  int message;
  int message_length;*/

  uint8_t conf = 0, iqr = 0;

  HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, 1);

  SX1272_Init();

  //uint8_t Rx = SX1272_Receive();

  //SX1272_Transmit(0x42);

  /*initialize hardware for LoRa module
  SX1278_hw.dio0.port = DIO0_GPIO_Port;
  SX1278_hw.dio0.pin = DIO0_Pin;
  SX1278_hw.nss.port = NSS_GPIO_Port;
  SX1278_hw.nss.pin = NSS_Pin;
  SX1278_hw.reset.port = RESET_GPIO_Port;
  SX1278_hw.reset.pin = RESET_Pin;
  SX1278_hw.spi = &hspi1;

  //initialize logic for LoRa module
  SX1278.hw = &SX1278_hw;

  //configure module
  printf("Configuring LoRa module\r\n");
  SX1278_begin(&SX1278, SX1278_433MHZ, SX1278_POWER_17DBM, SX1278_LORA_SF_8,
          SX1278_LORA_BW_20_8KHZ, 10);
  printf("Done configuring LoRaModule\r\n");

  //entry transmitter (master) or receiver (slave) mode
  if (master == 1) ret = SX1278_LoRaEntryTx(&SX1278, 16, 2000);
  else ret = SX1278_LoRaEntryRx(&SX1278, 16, 2000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint8_t u8RCVLen = 0;
  uint8_t PUTTY_BUFFER[50] = "V";
  printf("Test");

  HAL_UART_Transmit(&huart2, PUTTY_BUFFER, 9, HAL_MAX_DELAY);

  while (1)
  {
	  /*if (master == 1) {
		  printf("Master ...\r\n");
		  HAL_Delay(2500);
		  printf("Sending package...\r\n");

		  message_length = sprintf(buffer, "Hello %d", message);
		  ret = SX1278_LoRaEntryTx(&SX1278, message_length, 2000);
		  printf("Entry: %d\r\n", ret);

		  printf("Sending %s\r\n", buffer);
		  ret = SX1278_LoRaTxPacket(&SX1278, (uint8_t *) buffer, message_length, 2000);
		  message += 1;

		  printf("Transmission: %d\r\n", ret);
		  printf("Package sent...\r\n");

		  uint8_t txByte = 0x42;
		  uint8_t rxByte = SX1278_SPIRead(&SX1278, 0x42);
		  HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_RESET);
		  HAL_SPI_TransmitReceive(&hspi1, &txByte, &rxByte, 1, 1000);
		  txByte = 0x00;
		  HAL_SPI_TransmitReceive(&hspi1, &txByte, &rxByte, 1, 1000);
		  HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_SET);

		  printf("Version : %d\r\n", rxByte);

		/*uint8_t SEND = 0xAC;
		uint8_t RCV = 0;
		HAL_SPI_TransmitReceive(&hspi1, &SEND, &RCV, 1, HAL_MAX_DELAY);
		if(RCV == SEND) printf("OKAY !");*
	  } else {
		  printf("Slave ...\r\n");
		  HAL_Delay(1000);
		  printf("Receiving package...\r\n");

		  ret = SX1278_LoRaRxPacket(&SX1278);
		  printf("Received: %d\r\n", ret);
		  if (ret > 0) {
			  SX1278_read(&SX1278, (uint8_t *) buffer, ret);
			  printf("Content (%d): %s\r\n", ret, buffer);
		  }
		  printf("Package received ...\r\n");

	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


	  //SX1272_Transmit(0x42);
	  /*conf = SPI_Read_Register(0x01);
	  HAL_Delay(15);
	  iqr = SPI_Read_Register(0x12);*/
	  u8RCVLen = SX1272_Receive(PUTTY_BUFFER);

	  if(PUTTY_BUFFER[0] != 0) {
		  HAL_UART_Transmit(&huart2, PUTTY_BUFFER, u8RCVLen, HAL_MAX_DELAY);
		  PUTTY_BUFFER[0] = 0;
	  }
	  //HAL_Delay(500);

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 308;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
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
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : RESET_Pin */
  GPIO_InitStruct.Pin = RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RESET_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : DIO0_Pin */
  GPIO_InitStruct.Pin = DIO0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DIO0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DIO1_Pin DIO3_Pin DIO2_Pin */
  GPIO_InitStruct.Pin = DIO1_Pin|DIO3_Pin|DIO2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : NSS_Pin */
  GPIO_InitStruct.Pin = NSS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(NSS_GPIO_Port, &GPIO_InitStruct);

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
