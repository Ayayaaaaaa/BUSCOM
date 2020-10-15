/*
 * SX1272.h
 *
 *  Created on: 15 oct. 2020
 *      Authors: Thibault MOLLIER, Allan PACCOT
 */

#ifndef SX1272_H_
#define SX1272_H_

#include "main.h"

//! @brief : Initiate the LoRa shield
void SX1272_Init(void);

//! @brief : Write a register (SPI)
void SX1272_WriteRegister(uint8_t reg, uint8_t val);

#endif /* SX1272_H_ */
