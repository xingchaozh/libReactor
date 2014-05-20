/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : ClientConnector.h
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

#include "SvcHandler.h"

class ClientConnector :
	public SvcHandler
{
public:
	ClientConnector(SokectType socketType = SOCKET_TYPE_UDP, long timeOut = 1000);
	virtual ~ClientConnector(void);
public:
	void Initialize(string localHost, int localPort, string remoteHost, int remotePort);
	void SetEnable(bool bEnabled);
	SocketXO * GetUdpSocket() const { return m_socket; }
	void SetUdpSocket(SocketXO * val) { m_socket = val; }

	sockaddr_in GetServerAddr();
protected:
	virtual int HandleOutput() = 0;
	virtual int HandleInput() = 0;
private:
	virtual void ThreadEntryPoint();
protected:
	SokectType m_socketType;
	SocketXO * m_socket;
	bool m_bEnabled;

	struct sockaddr_in m_serverAddr;
	long m_timeOut;//milliseconds
};

