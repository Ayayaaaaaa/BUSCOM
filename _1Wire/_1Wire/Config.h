/*************************************
 * File name : Config.h
 * Author : Allan Paccot
 * Created on : 27/12/2019
 *************************************/

#ifndef CONFIG_H_
#define CONFIG_H_

#include "CPWD_HAL.h"
#include "CPWD_Types.h"

//! @briefs : Software version define
#define VERSION_SW       				0x0100        	// 0xAAbb = AA.bb

//! @briefs : defines for UART communication
#define ERROR_CMD						0x00

#define READ_CMD						0x01
#define WRITE_CMD						0x02

#endif /* CONFIG_H_ */
