/*
 * System.h
 *
 *  Created on:
 *      Author: VIB
 */

#ifndef COMUART_H_
#define COMUART_H_

#define NB_BYTE_DATA      16

#include "APA_HAL.h"
#include "APA_Types.h"

typedef struct
{
    U8 u8Commande;
    U16 u16Addresse;
    U8 au8Valeur[NB_BYTE_DATA];
} TsFrame;


void ComUart_Init(void);
void ComUart_Process(void);
void ComUart_BuildAndSendFrame(U8 u8IndexArg,TsFrame * sFrame);



#endif /* COMUART_H_ */
