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
	SocketXO * GetUdpSocket() const { return socket_; }
	void SetUdpSocket(SocketXO * val) { socket_ = val; }
protected:
	virtual int HandleInput() = 0;
private:
	virtual void ThreadEntryPoint();

protected:
	SokectType socketType_;
	SocketXO * socket_;
	bool enabled_;//whether the thread is enabled
	long timeOut_;//milliseconds
};
