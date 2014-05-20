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
	static sockaddr_in GetSockAddr(string localServerHost,int localServerPort);
	static int Select(int nfds, fd_set * readfds,fd_set * writefds,fd_set * exceptfds,timeval * timeout);
	static void FD_ZERO_X(fd_set * fds);
	static void FD_SET_X(SOCKET sock, fd_set * fds);
	static int FD_ISSET_X(SOCKET sock, fd_set * fds);

	virtual void Create(int af, int type, int protocol);
	int Bind(sockaddr * name);
	void Close();

	SOCKET GetSocket() const { return m_socket; }
	void SetSocket(SOCKET val) { m_socket = val; }
protected:
	SOCKET m_socket;
};


