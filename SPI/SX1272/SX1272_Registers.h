/*
 * SX1272_Regester.h
 *
 *  Created on: 15 oct. 2020
 *      Authors: Thibault MOLLIER, Allan PACCOT
 */


// Registers

#define ReqFifo 				0x00
#define RegOpMode 				0x01
#define RegFrMsb 				0x06
#define RegFrMib 				0x07
#define RegFrLsb 				0x08
#define RegFifoAddrPtr 			0x0D
#define RegFifoTxBaseAddr 		0x0E
#define RegFifoRxBaseAddr 		0x0F
#define RegFifoRxCurrentAddr 	0x10
#define RegIrqFlagsMask 		0x11
#define RegIrqFlags 			0x12
#define RegRxNbBytes 			0x13
#define RegPayloadLength		0x22

// Modes

#define FSK_SLEEP 				0x00
#define LORA_SLEEP 				0x80
#define LORA_STBY 				0x81
#define LORA_FSTX 				0x82
#define LORA_TX 				0x83
#define LORA_FSRX 				0x84
#define LORA_RX_CONTINUOUS 		0x85
#define LORA_RX_SINGLE 			0x86
