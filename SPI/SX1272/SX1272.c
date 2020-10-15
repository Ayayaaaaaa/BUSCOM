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

//! @last_edit : 15/10/2020
//! @details :
uint8_t SX1272_ReadRegister(uint8_t reg) {
	uint8_t data = 0;
	HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, 0);

	reg &= 0x7F;

	HAL_SPI_Transmit(&hspi1, &reg, 1, 1000);
	HAL_SPI_Receive(&hspi1, &data, 1, 1000);

	while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);

	HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, 1);

	return data;
}

//! @last_edit : 15/10/2020
//! @details :
void SX1272_BurstRead(uint8_t addr, uint8_t* rxBuf, uint8_t length) {
	if (length > 1) {
		HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_RESET);
		HAL_SPI_Transmit(&hspi1, &addr, 1, 1000);
		HAL_SPI_Receive(&hspi1, rxBuf, length, 1000);
		HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_SET);
	}
}

//! @last_edit : 15/10/2020
//! @details :
void SX1272_Transmit(uint8_t tx) {
	uint8_t addr = SX1272_ReadRegister(0x0E); // Tx base addr

	SX1272_WriteRegister(0x0D, addr); // write fifo addr ptr

	HAL_Delay(15);
	SX1272_WriteRegister(0x01, 0x81);

	HAL_Delay(15);
	SX1272_WriteRegister(0x00, tx);

	HAL_Delay(15);
	SX1272_WriteRegister(0x01, 0x82);

	HAL_Delay(15);
	SX1272_WriteRegister(0x01, 0x83);

	HAL_Delay(15);
	while((SX1272_ReadRegister(0x12) && 0x08)==0); // interrupt

	SX1272_WriteRegister(0x12, 0xFF); // clear interrupt
}

//! @last_edit : 15/10/2020
//! @details :
uint8_t SX1272_Receive(uint8_t rx[50]) {
	uint8_t length = 0;
	uint8_t addr = SX1272_ReadRegister(0x0F);//Rx base addr
	SX1272_WriteRegister(0x0D, addr);//write fifo addr ptr

	HAL_Delay(15);
	SX1272_WriteRegister(0x01, 0x81);
	HAL_Delay(15);
	SX1272_WriteRegister(0x01, 0x84);
	HAL_Delay(15);
	SX1272_WriteRegister(0x01, 0x85);
	HAL_Delay(15);


	while((SX1272_ReadRegister(0x12) && 0xC0)==0);//interrupt

	uint8_t interrupt = SX1272_ReadRegister(0x12);
	if(interrupt == 0x80){
		return 0;
	}

	addr = SX1272_ReadRegister(0x10);//Rx current addr
	length = SX1272_ReadRegister(0x13);//Rx current addr

	SX1272_WriteRegister(0x0D, addr);//write fifo addr ptr

	SX1272_BurstRead(0, rx, length);
	SX1272_WriteRegister(0x12, 0xFF);//clear interrupt
	return length;

}
