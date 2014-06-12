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

//typedef struct _UdpBuffer
//{
//	struct sockaddr_in sockAddr;
//	Buffer buffer;
//}UdpBuffer;

typedef struct _UdpBuffer
{
	SocketAddr sockAddr;
	Buffer buffer;
}UdpBuffer;

