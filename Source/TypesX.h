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

#include "ConstsX.h"

typedef char Buffer[MAX_DGRAM_BUFFER_SIZE];
typedef struct _BufferRev
{
	Buffer buffer;
	int length;
}BufferRev;

typedef struct _UdpBufferRev
{
	struct sockaddr_in fromAddr;
	BufferRev bufferRev;
}UdpBufferRev;
