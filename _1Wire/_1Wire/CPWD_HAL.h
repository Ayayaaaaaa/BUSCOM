/*************************************
 * File name : CPWD_HAL.h
 * Author : Allan Paccot
 * Created on : 08/01/2020
 *************************************/

#ifndef CPWD_HAL_H_
#define CPWD_HAL_H_

#include "stm32f4xx.h"
#include "main.h"

//! @brief : CPWD init, called in main.c
void CPWD_HAL_Init(void);

//! @brief : CPWD process, called in main.c, used to link ""system"" to ""main""
//!		Used to handle SysTime (1ms, 10ms, 100ms, 1s)
void CPWD_HAL_Process(void);

//! @brief : Tools for acting on GPIO
#define CPWD_GPIO_CLEAR(gpio)    (gpio##_GPIO_Port)->BSRR = ((gpio##_Pin) << 16);
#define CPWD_GPIO_SET(gpio)      (gpio##_GPIO_Port)->BSRR = (gpio##_Pin);
#define CPWD_GPIO_READ(gpio)     HAL_GPIO_ReadPin(gpio##_GPIO_Port,gpio##_Pin)
#define CPWD_GPIO_TOGGLE(gpio)   (gpio##_GPIO_Port)->ODR ^= (gpio##_Pin);

#endif /* CPWD_HAL_H_ */
