/*
 * System.c
 *
 *  Created on: 5 nov. 2020
 *      Author: allan
 */

#include "BusCom.h"

extern DAC_HandleTypeDef hdac;
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;
extern SPI_HandleTypeDef hspi2;
extern CAN_HandleTypeDef hcan1;

uint8_t b5sec = 0;
uint8_t bSpi = 0;
uint16_t u12DacValue = 0;
uint16_t u16AdcValue = 0, u16VoltageValue = 0;
uint8_t STR_BUFFER[100], STR_LEN = 0;
uint8_t SPI_BUFFER[100];
uint8_t CAN_BUFFER[100];
uint32_t CAN_RX_FIFO;

CAN_FilterTypeDef sFilterConfig;
CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;

void System_Init(void) {
	I2C_WriteRegister(RTC_SLAVE, 0x07, 0x00);
	I2C_WriteRegister(RTC_SLAVE, 0x00, 0x04);
	I2C_WriteRegister(RTC_SLAVE, 0x08, 0xC2);
	I2C_WriteRegister(RTC_SLAVE, 0x0F, 0x05);

	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, u12DacValue);
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);

	HAL_CAN_Start(&hcan1);

	TxHeader.StdId = 0x11;
	TxHeader.ExtId = 0;
	TxHeader.TransmitGlobalTime = DISABLE;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;

	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x11 << 5;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0xFFFF;
	sFilterConfig.FilterMaskIdLow = 0xFFFF;
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 14;

	HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig);
}

void System_Process(void) {
	uint32_t TxMailbox;

	if(b5sec) {
		I2C_WriteRegister(RTC_SLAVE, 0x07, 0x00);
		I2C_WriteRegister(RTC_SLAVE, 0x00, 0x04); //! Restart IT
		b5sec = 0;

		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, u12DacValue);
		if(u12DacValue < 3750) u12DacValue += 625;
		else u12DacValue = 0;

		HAL_Delay(1);

		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 1000);
		u16AdcValue = HAL_ADC_GetValue(&hadc1);
		u16VoltageValue = (uint16_t)(((float)3300 / 4096) * u16AdcValue);

		TxHeader.DLC = 2;
		HAL_CAN_AddTxMessage(&hcan1, &TxHeader, &u16VoltageValue, &TxMailbox);

		while(HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) != 3) {}; // Wait TX END

		while(HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0) == 0); // WAIT RX not EMPTy

		HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, CAN_BUFFER);

		HAL_SPI_TransmitReceive_IT(&hspi2, CAN_BUFFER, SPI_BUFFER, 2);
	}

	if(bSpi) {
		bSpi = 0;

		STR_LEN = sprintf(STR_BUFFER, "Voltage = %dmV  \r", (SPI_BUFFER[1] << 8) + SPI_BUFFER[0]);
		HAL_UART_Transmit(&huart2, STR_BUFFER, STR_LEN, 100);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	b5sec = 1;
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	bSpi = 1;
}
