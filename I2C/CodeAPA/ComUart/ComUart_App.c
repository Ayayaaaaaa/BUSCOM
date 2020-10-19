/*************************************
 * File name : ComUart_App.c
 * Author : Allan Paccot
 * Created on : 20/02/2020
 *************************************/

#include "ComUart_App.h"
#include "Config.h"
#include "System.h"

extern TsSystem sSystem;

//! @authors : Allan Paccot
//! @brief : Read command handle, private function
//! @param eFifo [in] : ID of the UART bus
//! @param sFrame [in] : Frame received
//void ComUartApp_PRV_ReadCMD(TeSerialFifo eFifo, TsFrame * sFrame);

//! @authors : Allan Paccot
//! @brief : Write command handle, private function
//! @param eFifo [in] : ID of the UART bus
//! @param sFrame [in] : Frame received
//void ComUartApp_PRV_WriteCMD(TeSerialFifo eFifo, TsFrame * sFrame);

//! @authors : Allan Paccot
//! @brief : Pairing commands handle
//! @param eFifo [in] : ID of the UART bus
//! @param sFrame [in] : Frame received
//void ComUartApp_PRV_PairingCMD(TeSerialFifo eFifo, TsFrame * sFrame);

//! @last_edit : 20/02/2020
//! @details : Initiate the ComUart
void ComUartApp_Init(void) {
	ComUart_Init();
}

//! @last_edit : 20/02/2020
//! @details : Communication UART process, handle low level UART process
void ComUartApp_Process(void) {
	ComUart_Process();
}

//! @last_edit : 06/03/2020
//! @details : Frame received handle
//! @param eFifo [in] : ID of the UART bus
//! @param sFrame [in] : Frame received
/*void ComUartApp_FrameReceived(TeSerialFifo eFifo, TsFrame * sFrame) {
	switch (sFrame->u8Commande) {
		case READ_CMD:
			ComUartApp_PRV_ReadCMD(eFifo, sFrame);
			break;
		case WRITE_CMD:
			ComUartApp_PRV_WriteCMD(eFifo, sFrame);
			break;
		case PAIRING_CMD:
			ComUartApp_PRV_PairingCMD(eFifo, sFrame);
			break;
		default:
			ComUartApp_SendError(eFifo);
			break;
	}
}*/

//! @last_edit : 27/02/2020
//! @details : Read command handle
//! @param eFifo [in] : ID of the UART bus
//! @param sFrame [in] : Frame received
/*void ComUartApp_PRV_ReadCMD(TeSerialFifo eFifo, TsFrame * sFrame) {
	switch (sFrame->u16Addresse) {
		case MODE_STATE_READ_ADDR:
			sFrame->au8Valeur[0] = sSystem.eState;
			ComUart_BuildAndSendFrame(eFifo, sFrame);
			break;
		case FAULT_READ_ADDR:
			sFrame->au8Valeur[0] = sSystem.eError;
			ComUart_BuildAndSendFrame(eFifo, sFrame);
			break;
		default:
			ComUartApp_SendError(eFifo);
			break;
	}
}*/

//! @last_edit : 12/03/2020
//! @details : Write commands handle
//! @param eFifo [in] : ID of the UART bus
//! @param sFrame [in] : Frame received
/*void ComUartApp_PRV_WriteCMD(TeSerialFifo eFifo, TsFrame * sFrame) {
	switch (sFrame->u16Addresse) {
		case WRITE_STATE_CMD_ADDR:
			if(sFrame->au8Valeur[0] >= 0 && sFrame->au8Valeur[0] <= 3 && sSystem.eMode == USER_MODE) {
				sSystem.eState = sFrame->au8Valeur[0];
				sSystem.bProgStart = false;
				if(sSystem.eState == STOP_STATE) System_RstTimeCounter();
			} else {
				ComUartApp_SendError(eFifo);
			}

			ComUartApp_SendState(eFifo);
			break;
		case WRITE_X_Y_Z_CMD_ADDR:
			if(sFrame->au8Valeur[1] <= 100) sControlMotor.u8IState_POURCENT[1] = sFrame->au8Valeur[1];
			if(sFrame->au8Valeur[2] <= 100) sControlMotor.u8IState_POURCENT[2] = sFrame->au8Valeur[2];
			if(sFrame->au8Valeur[3] <= 100) sControlMotor.u8IState_POURCENT[3] = sFrame->au8Valeur[3];

			// SETING THE CURENT WANTED FOR EACH STATE
			for(U8 i = 1; i < STATE_NUMBER; i++) sControlMotor.u16IState_mA[i] = (I_REF_mA * sControlMotor.u8IState_POURCENT[i]) / 100;

			break;
		case ACK_FAULT_CMD_ADDR:
			sSystem.eState = STOP_STATE;
			sSystem.eMode = USER_MODE;
			sSystem.eError = NO_ERROR;
			break;
		case WRITE_PROG_CMD_ADDR:
			sSystem.u8ProgRepeat = sFrame->au8Valeur[0];

			for(U8 i = 0; i < 3; i++) {
				sSystem.sProg[i].eState = sFrame->au8Valeur[(i * 2) + 1];
				sSystem.sProg[i].u8Duration_Min = sFrame->au8Valeur[(i * 2) + 2];
			}

			sSystem.bProgStart = true;
			break;
		default:
			ComUartApp_SendError(eFifo);
			break;
	}
}*/

//! @last_edit : 11/03/2020
//! @details : Pairing commands handle
//! @param eFifo [in] : ID of the UART bus
//! @param sFrame [in] : Frame received
/*void ComUartApp_PRV_PairingCMD(TeSerialFifo eFifo, TsFrame * sFrame) {
	switch (sFrame->u16Addresse) {
	case 0x1111:
		sSystem.bAckPairing = false;
		sSystem.bPairing = true;
		break;
	case 0x2222:
		sSystem.bAckPairing = true;
		sSystem.bPairing = false;
		break;
	default:
		ComUartApp_SendError(eFifo);
		break;
	}
}*/

//! @last_edit : 11/03/2020
//! @details : Send ACK pairing frame to ""eSerialFifo""
//! @param eSerialFifo [in] : ID of the UART bus
/*void ComUartApp_ACKPairing(TeSerialFifo eSerialFifo) {
    TsFrame sFrame;

    sFrame.u8Commande = READ_CMD;
    sFrame.u16Addresse = 0x1003;

    ComUart_BuildAndSendFrame(eSerialFifo, &sFrame);
}*/

//! @last_edit : 06/03/2020
//! @details : Send NACK pairing frame to ""eSerialFifo""
//! @param eSerialFifo [in] : ID of the UART bus
/*void ComUartApp_NACKPairing(TeSerialFifo eSerialFifo) {
    TsFrame sFrame;

    sFrame.u8Commande = PAIRING_CMD;
    sFrame.u16Addresse = 0xFFFF;

    ComUart_BuildAndSendFrame(eSerialFifo, &sFrame);
}*/

//! @last_edit : 12/03/2020
//! @details : Send the state frame to ""eSerialFifo""
//! @param eSerialFifo [in] : ID of the UART bus
/*void ComUartApp_SendState(TeSerialFifo eSerialFifo) {
    TsFrame sFrame;

    sFrame.u8Commande = READ_CMD;
    sFrame.u16Addresse = MODE_STATE_READ_ADDR;
    sFrame.au8Valeur[0] = sSystem.eState;

    ComUart_BuildAndSendFrame(eSerialFifo, &sFrame);
}*/

//! @last_edit : 27/02/2020
//! @details : Send an error frame to ""eSerialFifo""
//! @param eSerialFifo [in] : ID of the UART bus
/*void ComUartApp_SendError(TeSerialFifo eSerialFifo) {
    TsFrame sFrame;

    sFrame.u8Commande = ERROR_CMD;
    sFrame.u16Addresse = 0xFFFF;

    ComUart_BuildAndSendFrame(eSerialFifo, &sFrame);
}*/
