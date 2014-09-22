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
	Create();
}

UdpSocketXO::~UdpSocketXO(void)
{
}

void UdpSocketXO::Create()
{
	SocketXO::Create(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
}

int UdpSocketXO::RecvFrom(UdpBuffer & udpBuffer)
{
	return RecvFrom(udpBuffer.buffer.message,MAX_DGRAM_BUFFER_SIZE,udpBuffer.sockAddr);
}

int UdpSocketXO::RecvFrom(UCHAR8 * ptr, int len, SocketAddr & socketAddr)
{
	struct sockaddr_in addr;
	int len_addr = sizeof(addr);

	int ret =  RecvFrom(ptr,len,(sockaddr *)&addr,&len_addr);
	socketAddr = SocketXO::GetSockAddr(addr);
	return ret;
}

int UdpSocketXO::RecvFrom(UCHAR8 * ptr, int len, sockaddr * from, int * fromlen)
{
	return recvfrom(socket_,(char*)ptr,len,0,from,fromlen);
}

int UdpSocketXO::SendTo(UdpBuffer & udpBuffer)
{
	return SendTo(udpBuffer.buffer.message,udpBuffer.buffer.length,udpBuffer.sockAddr);
}

int UdpSocketXO::SendTo(UCHAR8 * ptr, int len, SocketAddr & socketAddr)
{
	sockaddr_in to = GetStdSockAddr(socketAddr);
	int tolen = sizeof(to);
	return SendTo(ptr,len,(sockaddr *)&to,tolen);
}

int UdpSocketXO::SendTo(UCHAR8 * ptr, int len, sockaddr * to, int tolen)
{
	return sendto(socket_,(char*)ptr,len,0,to,tolen);
}

