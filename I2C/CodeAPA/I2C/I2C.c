/*
 * I2C.c
 *
 *  Created on: 19 oct. 2020
 *      Author: allan
 */

#include "I2C.h"

extern I2C_HandleTypeDef hi2c3;
extern UART_HandleTypeDef huart2;

void I2C_Scanner(void) {
	U8 u8StrBuffer[100], u8StrLen = 0x00, u8Addr = 0x00;
	u8StrLen = sprintf (u8StrBuffer, "\n\rScanning : \n\r");
	HAL_UART_Transmit(&huart2, u8StrBuffer, u8StrLen, HAL_MAX_DELAY);
	u8StrLen = sprintf(u8StrBuffer, "     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n\r");
	HAL_UART_Transmit(&huart2, u8StrBuffer, u8StrLen, HAL_MAX_DELAY);

	while(u8Addr < 0x80) {
		u8StrLen = sprintf(u8StrBuffer, "%02X: ", u8Addr);

		// TODO : BETTER LOOP
		while((u8Addr & 0x0F) < 0x0F) {
			if(HAL_I2C_IsDeviceReady(&hi2c3, (u8Addr << 1), 1, HAL_MAX_DELAY)) {
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

		if(HAL_I2C_IsDeviceReady(&hi2c3, (u8Addr << 1), 1, HAL_MAX_DELAY)) {
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

void I2C_ReadRegister(U8 slave_addr, U8 register_addr, U8* receive_buffer, U8 len)
{
    // first set the register pointer to the register wanted to be read
    HAL_I2C_Master_Transmit(&hi2c3, slave_addr << 1, &register_addr, 1, 100);  // note the & operator which gives us the address of the register_pointer variable

    // receive the 2 x 8bit data into the receive buffer
    HAL_I2C_Master_Receive(&hi2c3, slave_addr << 1, receive_buffer, len, 100);
}
