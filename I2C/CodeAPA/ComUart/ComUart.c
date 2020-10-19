/*
 * System.c
 *
 *  Created on:
 *      Author: APA
 */

#include "ComUart.h"

#include "ComUart_App.h"

typedef enum
{
    WAIT_SOF,
    WAIT_CMD,
    WAIT_ADDRESS,
    WAIT_DATA,
    WAIT_CRC,
    WAIT_EOF,
} TeState;

#define NB_COM_UART     NB_SERIAL_FIFO

typedef struct
{
    U8 au8FrameRx[256];
    U8 au8FrameTx[256];
    TeState eState;

    TsFrame sFrame;
    U8 u8CRCcalcule;
    U8 u8CompteurInState;
}TsComUart;

TsComUart sComUart;
#define me sComUart


/***************************************************************************************************************************
 *  fonction  : ComUart_Init
 *  commentaire : 
 **************************************************************************************************************************/
void ComUart_Init(void)
{
	//SerialFifo_Init(SERIAL_BLE);
	me.eState = WAIT_SOF;
}

/***************************************************************************************************************************
 *  fonction  : ComUart_Process
 *  commentaire :
 **************************************************************************************************************************/
void ComUart_Process(void)
{
    U8 i;

	/*while (SerialFifo_Read(SERIAL_BLE, me.au8FrameRx))
	{
		switch (me.eState)
		{
			case WAIT_SOF:
				if (me.au8FrameRx[0] == 0x02)
				{
					me.eState = WAIT_CMD;
				}
				break;
			case WAIT_CMD:
				me.sFrame.u8Commande = me.au8FrameRx[0];  // M�morise la commande re�ue
				me.sFrame.u16Addresse = 0;
				me.u8CRCcalcule = me.au8FrameRx[0];
				for(i=0;i<NB_BYTE_DATA;i++)
				{
					me.sFrame.au8Valeur[i] = 0;
				}

				me.u8CompteurInState = 0;
				me.eState = WAIT_ADDRESS;
				break;
			case WAIT_ADDRESS:
				me.u8CRCcalcule += me.au8FrameRx[0];
				me.u8CompteurInState++;
				if (me.u8CompteurInState == 1)
				{
					me.sFrame.u16Addresse = (U16)me.au8FrameRx[0] << 8;
				}
				else if (me.u8CompteurInState == 2)
				{
					me.sFrame.u16Addresse += (U16)me.au8FrameRx[0];
					me.u8CompteurInState = 0;
					me.eState = WAIT_DATA;
				}
				break;
			case WAIT_DATA:
				me.u8CRCcalcule += me.au8FrameRx[0];

				if (me.u8CompteurInState < NB_BYTE_DATA)
				{
					me.sFrame.au8Valeur[me.u8CompteurInState] = me.au8FrameRx[0];
				}
				me.u8CompteurInState++;
				if (me.u8CompteurInState >= NB_BYTE_DATA)
				{
					me.u8CompteurInState = 0;
					me.eState = WAIT_CRC;
				}
				break;
			case WAIT_CRC:
				if (me.u8CRCcalcule == me.au8FrameRx[0])
				{
					me.eState = WAIT_EOF;
				}
				else
				{
					me.eState = WAIT_SOF;
				}
				break;
			case WAIT_EOF:
				if (me.au8FrameRx[0] == 0x03)
				{
					me.eState = WAIT_SOF;
					ComUartApp_FrameReceived(SERIAL_BLE, &me.sFrame);
				}
				me.eState = WAIT_SOF;
				break;
		}
	}*/
}

/***************************************************************************************************************************
 *  fonction  : ComUart_PRV_BuildAndSendFrame
 *  commentaire :
 **************************************************************************************************************************/
/*void ComUart_BuildAndSendFrame(TeSerialFifo serialFifo, TsFrame * sFrame)
{
    U8 indexEnCours, i;

    me.au8FrameTx[0] = 0x02;
    me.au8FrameTx[1] = sFrame->u8Commande;   // CMD
    me.au8FrameTx[2] = (sFrame->u16Addresse & 0xFF00) >> 8;   //@
    me.au8FrameTx[3] = sFrame->u16Addresse & 0x00FF;   // @

    indexEnCours = 4;
    for(i=0;i<(NB_BYTE_DATA);i++)
    {
    	me.au8FrameTx[indexEnCours] = sFrame->au8Valeur[i];
    	indexEnCours++;
    }

    me.au8FrameTx[indexEnCours] = 0;
    for(i=1;i<indexEnCours;i++)
    {
        me.au8FrameTx[indexEnCours] += me.au8FrameTx[i];  // CRC
    }

    indexEnCours++;
    me.au8FrameTx[indexEnCours] = 0x03;
    indexEnCours++;

    SerialFifo_Emission(serialFifo, me.au8FrameTx,indexEnCours);
}*/
