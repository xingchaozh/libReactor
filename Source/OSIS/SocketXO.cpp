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

sockaddr_in SocketXO::GetStdSockAddr(string localServerHost,int localServerPort)
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

sockaddr_in SocketXO::GetStdSockAddr(SocketAddr & socketAddr)
{
	return GetStdSockAddr(socketAddr.strAddress,socketAddr.port);
}

SocketAddr SocketXO::GetSockAddr(sockaddr_in & sockaddr)
{
	SocketAddr socketAddr;
	memset(&socketAddr,0,sizeof(SocketAddr));
	socketAddr.port = ntohs(sockaddr.sin_port);
	in_addr * in_addr_ = (in_addr*)(&(sockaddr.sin_addr.s_addr));
	memcpy(socketAddr.strAddress,inet_ntoa(*in_addr_),strlen(inet_ntoa(*in_addr_)));
	return socketAddr;
}

SocketAddr SocketXO::GetSockAddr(string host,int port)
{
	SocketAddr socketAddr;
	memset(&socketAddr,0,sizeof(SocketAddr));
	memcpy(socketAddr.strAddress,host.c_str(),host.length());
	socketAddr.port = port;
	return socketAddr;
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
	socket_ = socket(af,type,protocol);
	if(INVALID_SOCKET == socket_)
	{
		printf("socket() faild!\n");
		return;
	}
}

int SocketXO::Bind(sockaddr * addr)
{
	////bind socket to the host
	//printf("1\n");
	int ret = bind(socket_,addr,sizeof(sockaddr));
	//printf("2\n");
	if(SOCKET_ERROR == ret)
	{
		printf("bind() faild! code:%d\n", WSAGetLastError());
		Close();
	}
	return ret;
}

int SocketXO::Bind(SocketAddr & addr)
{
	////bind socket to the host
	return Bind((sockaddr *)&(GetStdSockAddr(addr)));
}

int SocketXO::Bind(string host,int port)
{
	return Bind(GetSockAddr(host,port));
}

void SocketXO::Close()
{
	closesocket(socket_);
}

int SocketXO::IsReadable(int timeOut)
{
	int errorCode;
	return IsReadable(socket_,&errorCode,timeOut);
}

int SocketXO::IsReadable(int socketId,int * errorCode,int timeOut) // milliseconds
{
	fd_set socketReadSet;

	//Initialize the set
	FD_ZERO_X(&socketReadSet);

	//put m_socket->GetSocket() into the set
	FD_SET_X(socketId,&socketReadSet);

	struct timeval tvTimeout;
	if (timeOut > 0)
	{
		tvTimeout.tv_sec  = timeOut / 1000;
		tvTimeout.tv_usec = (timeOut % 1000) * 1000;
	}
	else
	{
		tvTimeout.tv_sec  = 0;
		tvTimeout.tv_usec = 0;
	}

	//check the status of the socket I/O
	int ret = SocketXO::Select(socketId+1,&socketReadSet,0,0,&tvTimeout);
	if (ret == SOCKET_ERROR)
	{
		*errorCode = 1;
		return 0;
	}

	*errorCode = 0;
	return FD_ISSET_X(socketId,&socketReadSet) != 0;
} /* isReadable */


