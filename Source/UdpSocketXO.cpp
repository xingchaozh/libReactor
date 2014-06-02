/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : UdpSocketXO.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "UdpSocketXO.h"

UdpSocketXO::UdpSocketXO(void)
{
}

UdpSocketXO::~UdpSocketXO(void)
{
}

void UdpSocketXO::Create()
{
	SocketXO::Create(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
}

int UdpSocketXO::RecvFrom(char * ptr, int len, sockaddr * from, int * fromlen)
{
	return recvfrom(socket_,ptr,len,0,from,fromlen);
}

int UdpSocketXO::SendTo(char * ptr, int len, sockaddr * to, int tolen)
{
	return sendto(socket_,ptr,len,0,to,tolen);
}