/*************************************
 * File name : SigFox.c
 * Author : Allan Paccot
 * Created on : 29/09/2020
 *************************************/
#include <stdio.h>

#include "SigFox.h"
#include "Config.h"
#include "System.h"

extern TsSystem sSystem;
extern UART_HandleTypeDef huart1;

typedef enum {
	NOT_CONNECTED,
	IDLE,
	WaitOK,
	GotOK,
	WaitID,
	GotID,
	WaitPAC,
	GotPAC,
	SendTemp,
	ACKTemp,
} TeSigFox;

TeSigFox eSigFox = NOT_CONNECTED;

char ID[5];
char PAC[5];
U8 u8RxBuffer[50];
U8 u8ByteCount = 0;

//! @last_edit : 29/09/2020
//! @details :
void SigFox_Init(void) {
	sSystem.bSigFoxReady = false;
}

//! START OF PRV FUNCTIONS
//! @last_edit : 07/10/2020
//! @details :
void SigFox_Ask(void) {
	eSigFox = WaitOK;
	U8 u8TempTxBuffer[3] = "AT\n";
	HAL_UART_Receive_IT(&huart1, u8RxBuffer, 1); //! RCV ONE BY ONE
	HAL_UART_Transmit(&huart1, u8TempTxBuffer, 3, HAL_MAX_DELAY);
}

//! @last_edit : 07/10/2020
//! @details :
void SigFox_AskID(void) {
	eSigFox = WaitID;
	U8 u8TempTxBuffer[8] = "AT$I=10\n";
	HAL_UART_Receive_IT(&huart1, u8RxBuffer, 1); //! RCV ONE BY ONE
	HAL_UART_Transmit(&huart1, u8TempTxBuffer, 8, HAL_MAX_DELAY);
}

//! @last_edit : 07/10/2020
//! @details :
void SigFox_AskPAC(void) {
	eSigFox = WaitPAC;
	U8 u8TempTxBuffer[8] = "AT$I=11\n";
	HAL_UART_Receive_IT(&huart1, u8RxBuffer, 1); //! RCV ONE BY ONE
	HAL_UART_Transmit(&huart1, u8TempTxBuffer, 8, HAL_MAX_DELAY);
}
//! END OF PRV FUNCTIONS

//! @last_edit : 07/10/2020
//! @details :
void SigFox_Process(void) {
	switch(eSigFox) {
		case NOT_CONNECTED:
			SigFox_Ask();
			break;
		case GotOK:
			u8ByteCount = 0;
			SigFox_AskID();
			break;
		case GotID:
			u8ByteCount = 0;
			printf("ID : %s", u8RxBuffer);
			SigFox_AskPAC();
			break;
		case GotPAC:
			printf("PAC : %s", u8RxBuffer);
			eSigFox = IDLE;
			sSystem.bSigFoxReady = true;
			break;
		case ACKTemp:
			printf("%s", u8RxBuffer);
			eSigFox = IDLE;
			break;
		default:
			//! DO NOTHING
			break;
	}
}

//! @last_edit : 07/10/2020
//! @details :
void SigFox_SendTemp(void) {
	eSigFox = SendTemp;
	sSystem.bSigFoxReady = false;
	U8 u8TempTxBuffer[9] = "AT$SF=XX\n";
	u8TempTxBuffer[6] = 48 + (sSystem.s8Temp / 10);
	u8TempTxBuffer[7] = 48 + (sSystem.s8Temp % 10);

	HAL_UART_AbortReceive_IT(&huart1);
	HAL_UART_Receive_IT(&huart1, u8RxBuffer, 1); //! RCV ONE BY ONE
	HAL_UART_Transmit(&huart1, u8TempTxBuffer, 9, HAL_MAX_DELAY);
}

/***************************************************************************************************************************
 *  fonction  : HAL_UART_RxCpltCallback
 *  commentaire : callback pour les UART²
 **************************************************************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == huart1.Instance && eSigFox != IDLE) {
		if(u8RxBuffer[u8ByteCount] != '\n') { //! CHECK if this is the end of the CMD
			u8ByteCount++;
			HAL_UART_Receive_IT(&huart1, u8RxBuffer + u8ByteCount, 1); //! RCV ANOTHER ONE
		} else {
			eSigFox++;
		}
	}
}

/***************************************************************************************************************************
 *  fonction  : HAL_UART_TxCpltCallback
 *  commentaire : callback pour les UART²
 **************************************************************************************************************************/
//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if(huart->Instance == huart1.Instance) {
//
//	}
//}

/***************************************************************************************************************************
 *  fonction  : HAL_UART_ErrorCallback
 *  commentaire : callback de l'IT error UART
 **************************************************************************************************************************/
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == huart1.Instance) {
		u8ByteCount = 0;
		eSigFox = IDLE;

		HAL_UART_AbortReceive_IT(huart);
	}
}
