/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : TcpSocketXO.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "TcpSocketXO.h"

TcpSocketXO::TcpSocketXO(void)
{
}

TcpSocketXO::~TcpSocketXO(void)
{
}

void TcpSocketXO::Create()
{
	SocketXO::Create(AF_INET,SOCK_STREAM,IPPROTO_TCP);
}

