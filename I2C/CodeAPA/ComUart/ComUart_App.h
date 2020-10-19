/*************************************
 * File name : ComUart_App.h
 * Author : Allan Paccot
 * Created on : 20/02/2020
 *************************************/

#ifndef COMUART_APP_H_
#define COMUART_APP_H_

#include "ComUart.h"

//! @authors : Allan Paccot
//! @brief : Initiate the ComUart
void ComUartApp_Init(void);

//! @authors : Allan Paccot
//! @brief : Communication UART process, handle low level UART process
void ComUartApp_Process(void);

//! @authors : Allan Paccot
//! @brief : Frame received handle
//! @param eFifo [in] : ID of the UART bus
//! @param sFrame [in] : Frame received
//void ComUartApp_FrameReceived(TeSerialFifo eFifo, TsFrame * sFrame);

//! @authors : Allan Paccot
//! @brief : Send ACK pairing frame to ""eSerialFifo""
//! @param eSerialFifo [in] : ID of the UART bus
//void ComUartApp_ACKPairing(TeSerialFifo eSerialFifo);

//! @authors : Allan Paccot
//! @brief : Send NACK pairing frame to ""eSerialFifo""
//! @param eSerialFifo [in] : ID of the UART bus
//void ComUartApp_NACKPairing(TeSerialFifo eSerialFifo);

//! @authors : Allan Paccot
//! @brief : Send the state frame to ""eSerialFifo""
//! @param eSerialFifo [in] : ID of the UART bus
//void ComUartApp_SendState(TeSerialFifo eSerialFifo);

//! @authors : Allan Paccot
//! @brief : Send an error frame to ""eSerialFifo""
//! @param eSerialFifo [in] : ID of the UART bus
//void ComUartApp_SendError(TeSerialFifo eSerialFifo);

#endif /* COMUART_APP_H_ */
