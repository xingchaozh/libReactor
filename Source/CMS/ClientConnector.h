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
	ClientConnector(SokectType socketType = SOCKET_TYPE_UDP, long timeOut = 100);
	virtual ~ClientConnector(void);
public:
	int Initialize(string localClientHost, int localClientPort);
	void SetEnable(bool bEnabled);

	void SetTimeOut(long timeOut);
protected:
	virtual int ProcessOutput() = 0;
	
	virtual int HandleInput() = 0;
private:
	virtual void ThreadEntryPoint();
	void ProcessInput();

protected:
	SokectType socketType_;
	SocketXO * socket_;
	bool enabled_;
	long timeOut_;//milliseconds
};

