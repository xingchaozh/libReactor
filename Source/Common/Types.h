/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : Types.h
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#pragma once

#include "Consts.h"

#include <string>
using namespace std;

typedef unsigned short UShort;

typedef unsigned int UInt;

typedef unsigned short UINT16;

typedef unsigned int UINT32;

typedef unsigned char UCHAR8;

typedef struct _SocketAddr
{
	char strAddress[16];
	UShort port;
}SocketAddr;

typedef UCHAR8 Message[MAX_DGRAM_BUFFER_SIZE];
typedef struct _Buffer
{
	Message message;
	int length;
}Buffer;

typedef struct _UdpBuffer
{
	SocketAddr sockAddr;
	Buffer buffer;
}UdpBuffer;

typedef enum
{
	NET_BYTE_BIG_ENDIAN = 0x1,
	NET_BYTE_LITTLE_ENDIAN = 0x2,
}NET_BYTE_ORDER;


typedef enum
{
    EC_NO_FAULT,
    EC_RESERVED
}ErrorCode;

#define MAX_LENGTH_ERROR_MESSAGE 200
typedef struct _FaultElement
{
    ErrorCode errorCode;
    char errorMessage[MAX_LENGTH_ERROR_MESSAGE+1];
}FaultElement;

typedef FaultElement FaultElementArray[MAX_NUM_OF_FAULT_ELEMENT];


