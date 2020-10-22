/*
 * I2C.h
 *
 *  Created on: 19 oct. 2020
 *      Author: allan
 */

#ifndef I2C_I2C_H_
#define I2C_I2C_H_

#include "Config.h"

#define RTC_SLAVE			0x50
#define ACCEL_SLAVE			0x1D

void I2C_Scanner(void);
void I2C_ReadRegister(U8 slave_addr, U8 register_addr, U8* receive_buffer, U8 len);

#endif /* I2C_I2C_H_ */
