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
#include "DataHandler.h"

class UdpClientConnector :
	public ClientConnector
{
public:
	UdpClientConnector(void);
	~UdpClientConnector(void);
	LockFreeQueue<UdpBuffer> *  GetOutputBufferQueue();
	void SetDataHanler(DataHandler * dataHandler)
	{
		dataHandler_ = dataHandler;
	}
protected:
	virtual int HandleOutput();
	virtual int HandleInput();
	void ProcessData(UdpBuffer & bufferRev);
protected:
	LockFreeQueue<UdpBuffer> * queueOutput_;
	DataHandler * dataHandler_;
};
