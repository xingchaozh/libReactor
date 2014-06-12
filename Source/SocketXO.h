/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : SocketXO.h
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

#include "CommonX.h"

#include <string>
using namespace std;

typedef enum _SocketType
{
	SOCKET_TYPE_UNKNOWN,
	SOCKET_TYPE_UDP,
	SOCKET_TYPE_TCP
}SokectType;

class SocketXO
{
public:
	SocketXO(void);
public:
	virtual ~SocketXO(void);
public:
	static void StartupService();
	static void StopService();

	virtual void Create(int af, int type, int protocol);
	virtual void Create() = 0;
	int Bind(sockaddr * name);
	int Bind(SocketAddr & addr);
	int Bind(string host,int port);
	int IsReadable(int timeOut);
	void Close();

	static sockaddr_in GetStdSockAddr(string localServerHost,int localServerPort);
	static sockaddr_in GetStdSockAddr(SocketAddr & socketAddr);
	static SocketAddr GetSockAddr(sockaddr_in & sockaddr);
	static SocketAddr GetSockAddr(string host,int port);
protected:
	int IsReadable(int socketId,int * errorCode,int timeOut);
	void FD_ZERO_X(fd_set * fds);
	void FD_SET_X(SOCKET sock, fd_set * fds);
	int FD_ISSET_X(SOCKET sock, fd_set * fds);
	int Select(int nfds, fd_set * readfds,fd_set * writefds,fd_set * exceptfds,timeval * timeout);
protected:
	SOCKET socket_;
};

