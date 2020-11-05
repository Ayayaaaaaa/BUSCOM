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
	I2C_WriteRegister(ACCEL_SLAVE, 0x2D, 8);

	U8 _day     = (3*64)+(2*16)+1; // Days 21 / Year 3
	U8 _month   = (1*16)+2; // December
	I2C_WriteRegister(RTC_SLAVE, 0x05, _day);
	I2C_WriteRegister(RTC_SLAVE, 0x06, _month);
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
	U8 u8Time[3], u8XYZ[6], u8StrBuffer[100], u8StrLen = 0x00;
	S16 X = 0, Y = 0, Z = 0;
	float Xf = 0, Yf = 0, Zf = 0;
	U16 year, day, month;

	I2C_ReadRegister(RTC_SLAVE, 0x02, u8Time, 3);
	for(U8 i = 0; i < 3; i++) {
		u8Time[i] =  (u8Time[i] >> 4) * 10 + (u8Time[i] & 0x0F);
	}
	u8StrLen = sprintf (u8StrBuffer, "\n\rTime : %d:%d:%d\n\r", u8Time[2], u8Time[1], u8Time[0]);
	HAL_UART_Transmit(&huart2, u8StrBuffer, u8StrLen, HAL_MAX_DELAY);

	I2C_ReadRegister(RTC_SLAVE, 0x05, &day, 1);
	I2C_ReadRegister(RTC_SLAVE, 0x06, &month, 1);
	year     =   ((day & 0xC0) >> 6) + 2017;                               // Transform year
	day      =  (((day & 0x30) >> 4)*10    + (day & 0x0F)) & 0x3F;        // Transform day
	month    =  (((month & 0x10)  >> 4)*10 + (month & 0x0F)) & 0x3F;      // Transform month
	u8StrLen = sprintf (u8StrBuffer, "Date : %d/%d/%d\n\r", day, month, year);
	HAL_UART_Transmit(&huart2, u8StrBuffer, u8StrLen, HAL_MAX_DELAY);

	I2C_ReadRegister(ACCEL_SLAVE, 0x32, u8XYZ, 6);
	X = u8XYZ[0] | (u8XYZ[1] << 8);
	Y = u8XYZ[2] | (u8XYZ[3] << 8);
	Z = u8XYZ[4] | (u8XYZ[5] << 8);

	Xf = (float)X / 256;
	Yf = (float)Y / 256;
	Zf = (float)Z / 256;
	u8StrLen = sprintf (u8StrBuffer, "X : %f - Y : %f - Z : %f\n\r", Xf, Yf, Zf);
	HAL_UART_Transmit(&huart2, u8StrBuffer, u8StrLen, HAL_MAX_DELAY);
}
