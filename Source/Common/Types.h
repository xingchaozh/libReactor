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


typedef struct _SocketAddr
{
	char strAddress[16];
	UShort port;
}SocketAddr;

typedef char Message[MAX_DGRAM_BUFFER_SIZE];
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

