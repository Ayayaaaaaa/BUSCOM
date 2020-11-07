/*
 * I2C.c
 *
 *  Created on: 5 nov. 2020
 *      Author: allan
 */

#include "BusCom.h"

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;

void I2C_Scanner(void) {
	uint8_t u8StrBuffer[100], u8StrLen = 0x00, u8Addr = 0x00;
	u8StrLen = sprintf (u8StrBuffer, "\n\rScanning : \n\r");
	HAL_UART_Transmit(&huart2, u8StrBuffer, u8StrLen, HAL_MAX_DELAY);
	u8StrLen = sprintf(u8StrBuffer, "     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n\r");
	HAL_UART_Transmit(&huart2, u8StrBuffer, u8StrLen, HAL_MAX_DELAY);

	while(u8Addr < 0x80) {
		u8StrLen = sprintf(u8StrBuffer, "%02X: ", u8Addr);

		// TODO : BETTER LOOP
		while((u8Addr & 0x0F) < 0x0F) {
			if(HAL_I2C_IsDeviceReady(&hi2c1, (u8Addr << 1), 1, HAL_MAX_DELAY)) {
				u8StrBuffer[u8StrLen] = '-';
				u8StrLen++;
				u8StrBuffer[u8StrLen] = '-';
				u8StrLen++;
				u8StrBuffer[u8StrLen] = ' ';
				u8StrLen++;
			} else {
				u8StrBuffer[u8StrLen] = 'U';
				u8StrLen++;
				u8StrBuffer[u8StrLen] = 'U';
				u8StrLen++;
				u8StrBuffer[u8StrLen] = ' ';
				u8StrLen++;
			}
			u8Addr++;
		}

		if(HAL_I2C_IsDeviceReady(&hi2c1, (u8Addr << 1), 1, HAL_MAX_DELAY)) {
			u8StrBuffer[u8StrLen] = '-';
			u8StrLen++;
			u8StrBuffer[u8StrLen] = '-';
			u8StrLen++;
			u8StrBuffer[u8StrLen] = ' ';
			u8StrLen++;
		} else {
			u8StrBuffer[u8StrLen] = 'U';
			u8StrLen++;
			u8StrBuffer[u8StrLen] = 'U';
			u8StrLen++;
			u8StrBuffer[u8StrLen] = ' ';
			u8StrLen++;
		}

		u8Addr++;

		u8StrBuffer[u8StrLen] = '\n';
		u8StrLen++;
		u8StrBuffer[u8StrLen] = '\r';
		u8StrLen++;
		HAL_UART_Transmit(&huart2, u8StrBuffer, u8StrLen, HAL_MAX_DELAY);
	}
}

void I2C_WriteRegister(uint8_t slave_addr, uint8_t register_addr, uint8_t reg)
{
    uint8_t data[2];

    data[0] = register_addr;
    data[1] = reg;
    slave_addr = (slave_addr << 1) + 1;
    HAL_I2C_Master_Transmit(&hi2c1, slave_addr, data, 2, 100);  // data is the start pointer of our array
}

void I2C_ReadRegister(uint8_t slave_addr, uint8_t register_addr, uint8_t* receive_buffer, uint8_t len)
{
    // first set the register pointer to the register wanted to be read
    HAL_I2C_Master_Transmit(&hi2c1, slave_addr << 1, &register_addr, 1, 100);  // note the & operator which gives us the address of the register_pointer variable

    // receive the 2 x 8bit data into the receive buffer
    HAL_I2C_Master_Receive(&hi2c1, slave_addr << 1, receive_buffer, len, 100);
}
