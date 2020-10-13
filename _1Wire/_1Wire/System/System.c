/*************************************
 * File name : System.c
 * Author : Allan Paccot
 * Created on : 08/01/2020
 *************************************/

#include <stdio.h>

#include "System.h"
#include "_1Wire.h"
#include "SigFox.h"

TsSystem sSystem;
#define me sSystem

//! @last_edit : 20/02/2020
//! @details : Initiate the system, clearing variables and calling specifics functions
void System_Init(void) {
	me.bTempCaptConnected = false;
	me.s16RawTemp = 0;
	me.s8Temp = 0;

	SigFox_Init();
}

void System_Process(void) {

}

//! @last_edit : 08/01/2020
//! @details : Called each 1ms, ...
void System_Process1ms(void) {

}

//! @last_edit : 08/01/2020
//! @details : Called each 10ms, calling UART process, ...
void System_Process10ms(void) {
	static U8 u8TempoBTN = 0;

	if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)) {
		if(u8TempoBTN > 0) u8TempoBTN--;
	} else {
		if(u8TempoBTN < 0xFF) u8TempoBTN++;
	}

	if(u8TempoBTN >= 30 && me.bSigFoxReady) {
		SigFox_SendTemp();
	} else if(u8TempoBTN == 0) {
		me.bSigFoxReady = true;
	}
}

//! @last_edit : 19/02/2020
//! @details : Called each 100 ms, ...
void System_Process100ms(void) {
	SigFox_Process();

	if(me.bTempCaptConnected) {
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	} else {
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	}
}

//! @last_edit : 08/01/2020
//! @details : Called each 1s, ...
void System_Process1sec(void) {
	static U8 u8TempoS = 0;

	if(u8TempoS >= 2) {
		me.bTempCaptConnected = _1Wire_Reset();
		HAL_Delay(1);
		if(me.bTempCaptConnected) {
			_1Wire_WriteByte(0xCC);
			_1Wire_WriteByte(0x44);

			HAL_Delay(10);

			me.bTempCaptConnected = _1Wire_Reset();
			HAL_Delay(1);
			if(me.bTempCaptConnected) {
				_1Wire_WriteByte(0xCC);
				_1Wire_WriteByte(0xBE);
				me.s16RawTemp = _1Wire_ReadByte();
				me.s16RawTemp += _1Wire_ReadByte() << 8;

				me.s8Temp = 125 * me.s16RawTemp / 250;

				printf("Temp : %d°C\r\n", me.s8Temp);
			}
		}

		u8TempoS = 0;
	} else {
		u8TempoS++;
	}
}
