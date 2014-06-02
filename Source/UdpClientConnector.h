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
	LockFreeQueue<UdpBufferRev> *  GetBufferQueue();
	void SetTimeOut(long timeOut)
	{
		timeOut_ = timeOut;
	}
protected:
	virtual int HandleOutput();
	virtual int HandleInput();
	void ProcessData(UdpBufferRev * bufferRev);
protected:
	LockFreeQueue<UdpBufferRev> * queue_;
};
