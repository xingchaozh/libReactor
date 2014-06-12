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
	void Initialize(string localClientHost, int localClientPort, string remoteServerHost, int remoteServerPort);
	void SetEnable(bool bEnabled);

	SocketAddr GetServerAddr();
	void SetTimeOut(long timeOut);
protected:
	virtual int HandleOutput() = 0;
	virtual int HandleInput() = 0;
private:
	virtual void ThreadEntryPoint();

protected:
	SokectType socketType_;
	SocketXO * socket_;
	bool enabled_;

	SocketAddr serverAddr_;
	long timeOut_;//milliseconds
};

