/*************************************
 * File name : System.h
 * Author : Allan Paccot
 * Created on : 08/01/2020
 *************************************/

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "Config.h"

//! @brief : Main struct of the system, contain every useful global variables
typedef struct {
	bool bTempCaptConnected;
	U16 s16RawTemp;
	S8 s8Temp;

	bool bSigFoxReady;
} TsSystem;

//! @brief : Initiate the system
void System_Init(void);

void System_Process(void);

//! @brief : Called each 1ms
void System_Process1ms(void);

//! @brief : Called each 10ms
void System_Process10ms(void);

//! @brief : Called each 100ms
void System_Process100ms(void);

//! @brief : Called each 1s
void System_Process1sec(void);

#endif /* SYSTEM_H_ */
