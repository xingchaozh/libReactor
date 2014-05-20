/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : SocketXO.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "SocketXO.h"

SocketXO::SocketXO(void)
{
}

SocketXO::~SocketXO(void)
{
	Close();
}

void SocketXO::StartupService()
{
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2, 2),&wsa) != 0)
	{
		printf("WSAStartup() failed!\n");
		return;
	}
}

void SocketXO::StopService()
{
	WSACleanup();
}

sockaddr_in SocketXO::GetSockAddr(string localServerHost,int localServerPort)
{
	struct sockaddr_in localAddr;
	//set protocol family
	localAddr.sin_family = AF_INET;
	//set host port
	localAddr.sin_port = htons(localServerPort);
	//Struct sin_addr is  used to defind IP address,  it's a property of addr_in.
	//It's nest three structs as S_un_b, S_un_w and S-un.(union)
	localAddr.sin_addr.s_addr= inet_addr(localServerHost.c_str());//htonl(INADDR_ANY);
	return localAddr;
}

int SocketXO::Select(int nfds, fd_set * readfds,fd_set * writefds,fd_set * exceptfds,timeval * timeout)
{
	//int select(int nfds, fd_set * readfds,fd_set * writefds,fd_set * exceptfds,timeval * timeout);
	return select(nfds, readfds,writefds,exceptfds,timeout);
}

void SocketXO::FD_ZERO_X(fd_set * fds)
{
	FD_ZERO(fds);
}

void SocketXO::FD_SET_X(SOCKET sock, fd_set * fds)
{
	FD_SET(sock,fds);
}

int SocketXO::FD_ISSET_X(SOCKET sock, fd_set * fds)
{
	return FD_ISSET(sock,fds);
}

void SocketXO::Create(int af, int type, int protocol)
{
	/*
	*first param is protocol family, generally AF_INET for IP internet.  
	*second param is type of socket, SOCK_DGRAM is for Data Gram£¨UDP£©, and SOCK_STREAM is for TCP.  
	*the last param is communicate protocol. Generally is zero.  
	*/ 
	//SOCKET socket(int af, int type, int protocol);
	//m_socket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	m_socket = socket(af,type,protocol);
	if(INVALID_SOCKET == m_socket)
	{
		StopService();
		printf("socket() faild!\n");
		return;
	}
}

int SocketXO::Bind(sockaddr * addr)
{
	////bind socket to the host
	int ret = bind(m_socket,addr,sizeof(sockaddr));
	if(SOCKET_ERROR == ret)
	{
		printf("bind() faild! code:%d\n", WSAGetLastError());
		Close();
		StartupService();
	}
	return ret;
}

void SocketXO::Close()
{
	closesocket(m_socket);
}



