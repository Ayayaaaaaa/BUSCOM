/*************************************
 * File name : APA_HAL.h
 * Author : Allan Paccot
 * Created on : 08/01/2020
 *************************************/

#ifndef APA_HAL_H_
#define APA_HAL_H_

#include "stm32f4xx.h"
#include "main.h"

//! @brief : APA init, called in main.c
void APA_HAL_Init(void);

//! @brief : APA process, called in main.c, used to link ""system"" to ""main""
//!		Used to handle SysTime (1ms, 10ms, 100ms, 1s)
void APA_HAL_Process(void);

//! @brief : Tools for acting on GPIO
#define APA_GPIO_CLEAR(gpio)    (gpio##_GPIO_Port)->BSRR = ((gpio##_Pin) << 16);
#define APA_GPIO_SET(gpio)      (gpio##_GPIO_Port)->BSRR = (gpio##_Pin);
#define APA_GPIO_READ(gpio)     HAL_GPIO_ReadPin(gpio##_GPIO_Port,gpio##_Pin)
#define APA_GPIO_TOGGLE(gpio)   (gpio##_GPIO_Port)->ODR ^= (gpio##_Pin);

#endif /* APA_HAL_H_ */
