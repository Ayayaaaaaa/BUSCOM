/*************************************
 * File name : _1Wire.c
 * Author : Allan Paccot
 * Created on : 19/00/2020
 *************************************/

#include "_1Wire.h"
U16 test = 0;
TIM_HandleTypeDef htim1;

//! Private Functions
//! Simple delay function, blocking
void DelayUS(U16 u16uS) {
	__HAL_TIM_ENABLE(&htim1); //! Start the counter
	__HAL_TIM_SET_COUNTER(&htim1,0);

	while(__HAL_TIM_GET_COUNTER(&htim1) < u16uS) { }

	__HAL_TIM_DISABLE(&htim1); //! Stop the counter
}

void _1Wire_WriteBit0(void) {
	HAL_GPIO_WritePin(_1W_PIN_GPIO_Port, _1W_PIN_Pin, GPIO_PIN_RESET);//_1W_PIN_GPIO_Port->BSRR = _1W_PIN_Pin << 16U; //! Drive bus LOW
	DelayUS(60); //! Sleep time 1

	HAL_GPIO_WritePin(_1W_PIN_GPIO_Port, _1W_PIN_Pin, GPIO_PIN_SET);//_1W_PIN_GPIO_Port->BSRR = _1W_PIN_Pin; //! Releasing bus
	DelayUS(10); //! Recovery time
}

void _1Wire_WriteBit1(void) {
	HAL_GPIO_WritePin(_1W_PIN_GPIO_Port, _1W_PIN_Pin, GPIO_PIN_RESET);//_1W_PIN_GPIO_Port->BSRR = _1W_PIN_Pin << 16U; //! Drive bus LOW
	DelayUS(6); //! Sleep time 1

	HAL_GPIO_WritePin(_1W_PIN_GPIO_Port, _1W_PIN_Pin, GPIO_PIN_SET);//_1W_PIN_GPIO_Port->BSRR = _1W_PIN_Pin; //! Releasing bus
	DelayUS(64); //! Sleep time 2 (54) + Recovery time (10)
}

GPIO_PinState _1Wire_ReadBit(void) {
	GPIO_PinState stPin; //! Bus status variable

	HAL_GPIO_WritePin(_1W_PIN_GPIO_Port, _1W_PIN_Pin, GPIO_PIN_RESET);//_1W_PIN_GPIO_Port->BSRR = _1W_PIN_Pin << 16U; //! Drive bus LOW
	DelayUS(6); //! Sleep time 1

	HAL_GPIO_WritePin(_1W_PIN_GPIO_Port, _1W_PIN_Pin, GPIO_PIN_SET);//_1W_PIN_GPIO_Port->BSRR = _1W_PIN_Pin; //! Releasing bus
	DelayUS(9); //! Sleep time 2

	stPin = HAL_GPIO_ReadPin(_1W_PIN_GPIO_Port, _1W_PIN_Pin);//(_1W_PIN_GPIO_Port->IDR & _1W_PIN_Pin) != GPIO_PIN_RESET; //! Sampling the bus
	DelayUS(55); //! Sleep time 2 (45) + Recovery time (10)

	return stPin;
}

bool _1Wire_Reset(void) {
	bool bSensor; //! Sensor presence

	HAL_GPIO_WritePin(_1W_PIN_GPIO_Port, _1W_PIN_Pin, GPIO_PIN_RESET); //_1W_PIN_GPIO_Port->BSRR = _1W_PIN_Pin << 16U; //! Drive bus LOW
	DelayUS(480); //! Sleep time 1

	HAL_GPIO_WritePin(_1W_PIN_GPIO_Port, _1W_PIN_Pin, GPIO_PIN_SET); //1W_PIN_GPIO_Port->BSRR = _1W_PIN_Pin; //! Releasing bus
	DelayUS(70); //! Sleep time 2

	bSensor = !HAL_GPIO_ReadPin(_1W_PIN_GPIO_Port, _1W_PIN_Pin); //(_1W_PIN_GPIO_Port->IDR & _1W_PIN_Pin) == GPIO_PIN_RESET; //! Sampling the bus
	DelayUS(55); //! Sleep time 2 (45) + Recovery time (10)

	return bSensor;
}

U8 _1Wire_ReadByte(void) {
	U8 u8Byte = 0;

	for(U8 i = 0; i < 8; i++) { //! Go trough all bits
		u8Byte += ((U8)_1Wire_ReadBit() << i); //! Read and add to buffer
	}

	return u8Byte;
}

void _1Wire_WriteByte(U8 u8Byte) {
	for(U8 i = 0; i < 8; i++) { //! Go trough all bits
		if((u8Byte >> i) & 1) _1Wire_WriteBit1(); //! Write a 1
		else _1Wire_WriteBit0(); //! Write a 0
	}
}
