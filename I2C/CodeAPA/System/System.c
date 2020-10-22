/*************************************
 * File name : System.c
 * Author : Allan Paccot
 * Created on : 08/01/2020
 *************************************/

#include "System.h"
#include "ComUart_App.h"
#include "I2C.h"

extern UART_HandleTypeDef huart2;

TsSystem sSystem;
#define me sSystem

//! @last_edit : 20/02/2020
//! @details : Initiate the system, clearing variables and calling specifics initiate functions
void System_Init(void) {
	I2C_Scanner();
}

void System_Process(void) {

}

//! @last_edit : 08/01/2020
//! @details : Called each 1ms
void System_Process1ms(void) {

}

//! @last_edit : 08/01/2020
//! @details : Called each 10ms
void System_Process10ms(void) {

}

//! @last_edit : 19/02/2020
//! @details : Called each 100 ms
void System_Process100ms(void) {
	/*static U8 testAddr = 0x00, i = 0;
	static U8 validAddr[2];

	bool result = HAL_I2C_IsDeviceReady(&hi2c3, (testAddr), 1, HAL_MAX_DELAY);

	if(!result && i <= 1) {
		validAddr[i] = testAddr;
		i++;
		testAddr++;
	}

	testAddr++;*/
}

//! @last_edit : 08/01/2020
//! @details : Called each 1s
void System_Process1sec(void) {
	U8 u8Time[3], u8StrBuffer[100], u8StrLen = 0x00;


	I2C_ReadRegister(RTC_SLAVE, 0x02, u8Time, 3);
	for(U8 i = 0; i < 3; i++) {
		u8Time[i] =  (u8Time[i] >> 4) * 10 + (u8Time[i] & 0x0F);
	}
	u8StrLen = sprintf (u8StrBuffer, "\n\rTime : %d:%d:%d\n\r", u8Time[2], u8Time[1], u8Time[0]);
	HAL_UART_Transmit(&huart2, u8StrBuffer, u8StrLen, HAL_MAX_DELAY);

}
