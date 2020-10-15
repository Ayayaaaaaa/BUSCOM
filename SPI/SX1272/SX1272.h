/*
 * SX1272.h
 *
 *  Created on: 15 oct. 2020
 *      Authors: Thibault MOLLIER, Allan PACCOT
 */

#ifndef SX1272_H_
#define SX1272_H_

#include "main.h"

#define RCV_BUFFER_MAX_LEN		50

//! @brief : Initiate the LoRa shield
void SX1272_Init(void);

//! @brief : Write a register (SPI)
//! @param in [reg] : Register to write
//! @param in [val] : Value to write in the register
void SX1272_WriteRegister(uint8_t reg, uint8_t val);

//! @brief : Read a register (SPI)
//! @param in [reg] : Register to read
uint8_t SX1272_ReadRegister(uint8_t reg);

//! @brief : Read registers in burst mode (SPI)
//! @param in [addr] : Base register to read
//! @param out [rxBuf] : buffer for readed value
//! @param in[length] : Byte number to read
void SX1272_BurstRead(uint8_t addr, uint8_t* rxBuf, uint8_t length);

//! @brief : Read registers in burst mode (SPI)
//! @param in [tx] : Byte to send
void SX1272_Transmit(uint8_t tx);

//! @brief : Read registers in burst mode (SPI)
//! @param in [rx] : Byte buffer to read
uint8_t SX1272_Receive(uint8_t rx[RCV_BUFFER_MAX_LEN]);

#endif /* SX1272_H_ */
