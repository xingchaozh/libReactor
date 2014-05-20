/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : ServerAccepter.h
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

class ServerAccepter :
	public SvcHandler
{
public:
	ServerAccepter(SokectType socketType = SOCKET_TYPE_UDP, long timeOut = 1000);
	ServerAccepter(string localHost, int localPort, SokectType m_socketType = SOCKET_TYPE_UDP, long timeOut = 1000);
	virtual ~ServerAccepter(void);

public:
	void Initialize(string localHost,int localPort);
	void SetEnable(bool bEnabled);
	SocketXO * GetUdpSocket() const { return m_socket; }
	void SetUdpSocket(SocketXO * val) { m_socket = val; }
protected:
	virtual int HandleInput() = 0;
private:
	virtual void ThreadEntryPoint();

protected:
	SokectType m_socketType;
	SocketXO * m_socket;
	bool m_bEnabled;//whether the thread is enabled
	long m_timeOut;//milliseconds
};
