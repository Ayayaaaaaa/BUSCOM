/*************************************
 * File name : System.c
 * Author : Allan Paccot
 * Created on : 08/01/2020
 *************************************/

#include "System.h"
#include "ComUart_App.h"
#include "I2C.h"

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

}
