/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : UdpClientConnector.h
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
#include "ClientConnector.h"

#include "LockFreeQueues.h"

class UdpClientConnector :
	public ClientConnector
{
public:
	UdpClientConnector(void);
	~UdpClientConnector(void);
	LockFreeQueues *  GetBufferQueue();
	void SetTimeOut(long timeOut)
	{
		m_timeOut = timeOut;
	}
protected:
	virtual int HandleOutput();
	virtual int HandleInput();
	void ProcessData(UdpBufferRev * bufferRev);
protected:
	LockFreeQueues * m_queue;
};
