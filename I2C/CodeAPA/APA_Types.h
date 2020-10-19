/*************************************
 * File name : APA_Types.h
 * Author : Allan Paccot
 * Created on : 08/01/2020
 *************************************/

#ifndef APA_TYPES_H_
#define APA_TYPES_H_

/*********************/// BETTER TYPES ///*********************/
typedef unsigned char U8;
typedef signed char S8;
typedef unsigned short U16;
typedef signed short S16;
typedef unsigned long U32;
typedef signed long S32;
typedef unsigned long long U64;
typedef signed long long S64;

#ifndef bool
typedef enum { true = 1, false = 0 } bool;
#endif
/**************************************************************/

/**********************/// MAX VALUE ///***********************/
#define U32_MAX    	0xFFFFFFFF
#define U16_MAX    	0xFFFF
#define U8_MAX    	0xFF
/**************************************************************/

/*********************/// BUFFER MANIP ///*********************/
#define ENTIER_TO_BUFFER(a,b)    ((a >> b) & 0xFF)

#define BUFFER_TO_U16(buff,index)  ((((U16)buff[index]) << 8) + ((U16)buff[index+1]) )
#define BUFFER_TO_U32(buff,index)  ((((U32)buff[index]) << 24) + (((U32)buff[index+1]) << 16) + (((U32)buff[index+2]) << 8) + (((U32)buff[index+3])) )

#define U16_TO_BUFFER(buffer,index,valeur16bit)\
{\
    buffer[index] = ENTIER_TO_BUFFER(valeur16bit,8);\
    buffer[index+1] = ENTIER_TO_BUFFER(valeur16bit,0);\
}

#define U32_TO_BUFFER(buffer,index,valeur32bit)\
{\
    buffer[index] = ENTIER_TO_BUFFER(valeur32bit,24);\
    buffer[index+1] = ENTIER_TO_BUFFER(valeur32bit,16);\
    buffer[index+2] = ENTIER_TO_BUFFER(valeur32bit,8);\
    buffer[index+3] = ENTIER_TO_BUFFER(valeur32bit,0);\
}

#define BUFFER_TO_BUFFER(bufferIn, indexIn, bufferOut, indexOut, len)\
{\
	for(U32 i = 0; i < len; i++) {\
		bufferOut[indexOut + i] = bufferIn[indexIn + i];\
	}\
}
/**************************************************************/

#endif /* APA_TYPES_H_ */
