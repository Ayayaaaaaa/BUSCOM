/*
 * BusCom.h
 *
 *  Created on: 5 nov. 2020
 *      Author: allan
 */

#ifndef BUSCOM_H_
#define BUSCOM_H_

#define RTC_SLAVE			0x50
#define ACCEL_SLAVE			0x1D

#include "main.h"

void I2C_Scanner(void);
void I2C_ReadRegister(uint8_t slave_addr, uint8_t register_addr, uint8_t* receive_buffer, uint8_t len);
void I2C_WriteRegister(uint8_t slave_addr, uint8_t register_addr, uint8_t reg);


#endif /* BUSCOM_H_ */
