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
	ClientConnector(SokectType socketType = SOCKET_TYPE_UDP, long timeOut = 500);
	virtual ~ClientConnector(void);
public:
	void Initialize(string localHost, int localPort, string remoteHost, int remotePort);
	void SetEnable(bool bEnabled);

	SocketXO * GetUdpSocket() const { return socket_; }
	void SetUdpSocket(SocketXO * val) { socket_ = val; }

	sockaddr_in GetServerAddr();
protected:
	virtual int HandleOutput() = 0;
	virtual int HandleInput() = 0;
private:
	virtual void ThreadEntryPoint();

protected:
	SokectType socketType_;
	SocketXO * socket_;
	bool enabled_;

	struct sockaddr_in serverAddr_;
	long timeOut_;//milliseconds
};

