/*************************************
 * File name : _1Wire.h
 * Author : Allan Paccot
 * Created on : 19/00/2020
 *************************************/
#ifndef _1WIRE_H_
#define _1WIRE_H_

#include "Config.h"

bool 	_1Wire_Reset		(void);
U8 		_1Wire_ReadByte		(void);
void 	_1Wire_WriteByte	(U8 u8Byte);

void _1Wire_WriteBit0(void);
void _1Wire_WriteBit1(void);
GPIO_PinState _1Wire_ReadBit(void);

#endif /* _1WIRE_H_ */
