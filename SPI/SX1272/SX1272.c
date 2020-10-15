/*
 * SX1272.c
 *
 *  Created on: 15 oct. 2020
 *      Authors: Thibault MOLLIER, Allan PACCOT
 */

#include "SX1272.h"

extern SPI_HandleTypeDef hspi1;

//! @last_edit : 15/10/2020
//! @details :
void SX1272_Init(void) {
	SX1272_WriteRegister(0x01, 0x00);

	HAL_Delay(15);
	SX1272_WriteRegister(0x01, 0x80);

	HAL_Delay(15);
	SX1272_WriteRegister(0x06, 0xD9); //Frequency 868.5MHz : 0xD92000
	SX1272_WriteRegister(0x07, 0x20);
	SX1272_WriteRegister(0x08, 0x00);
}

//! @last_edit : 15/10/2020
//! @details :
void SX1272_WriteRegister(uint8_t reg, uint8_t val) {
	  HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, 0);

	  reg |= 0x80; //! MASK FOR R/W BIT

	  HAL_SPI_Transmit(&hspi1, &reg, 1, 1000);
	  HAL_SPI_Transmit(&hspi1, &val, 1, 1000);

	  //! WAIT FOR SPI
	  while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);

	  HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, 1);
}
