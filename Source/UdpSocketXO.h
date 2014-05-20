/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : UdpSocketXO.h
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
#include "socketxo.h"
class UdpSocketXO :
	public SocketXO
{
public:
	UdpSocketXO(void);
	~UdpSocketXO(void);
public:
	void Create();
	int RecvFrom(char * ptr, int len, sockaddr * from, int * fromlen);
	int SendTo(char * ptr, int len, sockaddr * to, int tolen);
};
