/*************************************
 * File name : CPWD_HAL.c
 * Author : Allan Paccot
 * Created on : 08/01/2020
 *************************************/

#include "CPWD_HAL.h"
#include "CPWD_Types.h"

#include "System.h"

extern UART_HandleTypeDef huart2;

//! @brief : Flags for SysTime handling
U8 Tick1Ms = 0;
U8 Tick10Ms = 0;
U8 Tick100Ms = 0;
U8 Tisk1s = 0;

//! @last_edit : 08/01/2020
//! @details : CPWD init, called in main.c, simply call ""system_init""
void CPWD_HAL_Init(void) {
	System_Init();
}

//! @last_edit : 08/01/2020
//! @details : CPWD process, called in main.c, used to link ""system"" to ""main""
//!		Used to handle SysTime (1ms, 10ms, 100ms, 1s)
void CPWD_HAL_Process(void) {
	System_Process();

	if(Tick1Ms != 0) {
		Tick1Ms = 0; // RESETING FLAG
		System_Process1ms();
	}

	if(Tick10Ms != 0) {
		Tick10Ms = 0; // RESETING FLAG
		System_Process10ms();
	}

	if(Tick100Ms != 0) {
		Tick100Ms = 0; // RESETING FLAG
		System_Process100ms();
	}

	if(Tisk1s != 0) {
		Tisk1s = 0; // RESETING FLAG
		System_Process1sec();
	}
}

//! @last_edit : 08/01/2020
//! @details : SYSTICK CALLBACK, called each ms, counting to provide a SysTime (1ms, 10ms, 100ms, 1s)
void HAL_SYSTICK_Callback(void) {
	static U16 sousCompteur10ms = 0;
	static U16 sousCompteur100ms = 0;
	static U16 sousCompteur1s = 0;

	Tick1Ms = 1;

	sousCompteur10ms++;
	if(sousCompteur10ms >= 10) {
		Tick10Ms = 1; // RAISING FLAG
		sousCompteur10ms = 0;
	}

	sousCompteur100ms++;
	if(sousCompteur100ms >= 100) {
		Tick100Ms = 1; // RAISING FLAG
		sousCompteur100ms = 0;
	}

	sousCompteur1s++;
	if(sousCompteur1s > 1000) {
		Tisk1s = 1; // RAISING FLAG
		sousCompteur1s = 0;
	}
}


//! @last_edit : 10/07/2020
//! @details : PRINTF TO UART handling
int __io_putchar(int ch)
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USARTx and Loop until the end of transmission */
	while (HAL_OK != HAL_UART_Transmit(&huart2, (uint8_t *) &ch, 1, HAL_MAX_DELAY))
	{
		;
	}
	return ch;
}
