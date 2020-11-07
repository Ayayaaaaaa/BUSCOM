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

uint8_t b5sec = 0;
uint16_t u12DacValue = 0;
uint16_t u16AdcValue = 0, u16VoltageValue = 0;
uint8_t STR_BUFFER[100], STR_LEN = 0;
uint8_t SPI_BUFFER[100];

void System_Init(void) {
	I2C_WriteRegister(RTC_SLAVE, 0x07, 0x00);
	I2C_WriteRegister(RTC_SLAVE, 0x00, 0x04);
	I2C_WriteRegister(RTC_SLAVE, 0x08, 0xC2);
	I2C_WriteRegister(RTC_SLAVE, 0x0F, 0x05);

	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, u12DacValue);
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
}

void System_Process(void) {
	if(b5sec) {
		I2C_WriteRegister(RTC_SLAVE, 0x07, 0x00);
		I2C_WriteRegister(RTC_SLAVE, 0x00, 0x04); //! Restart IT

		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, u12DacValue);
		if(u12DacValue < 3750) u12DacValue += 625;
		else u12DacValue = 0;

		HAL_Delay(1);

		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 1000);
		u16AdcValue =  HAL_ADC_GetValue(&hadc1);
		u16VoltageValue = (uint16_t)(((float)3300 / 4096) * u16AdcValue);

		STR_LEN = sprintf(STR_BUFFER, "Voltage = %dmV\r\n", u16VoltageValue);

		HAL_SPI_TransmitReceive(&hspi2, STR_BUFFER, SPI_BUFFER, STR_LEN, 100);
		HAL_UART_Transmit(&huart2, SPI_BUFFER, STR_LEN, 100);

		b5sec = 0;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	b5sec = 1;
}
