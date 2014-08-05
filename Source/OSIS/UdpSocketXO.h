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
	int RecvFrom(UdpBuffer & udpBuffer);
	int SendTo(UdpBuffer & udpBuffer);
protected:
	void Create();
	int RecvFrom(char * ptr, int len, sockaddr * from, int * fromlen);
	int RecvFrom(char * ptr, int len, SocketAddr & socketAddr);
	int SendTo(char * ptr, int len, sockaddr * to, int tolen);
	int SendTo(char * ptr, int len, SocketAddr & socketAddr);
};
