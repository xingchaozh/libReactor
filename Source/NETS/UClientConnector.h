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

#include "LockFreeQueue.h"
#include "../IF/DataHandler.h"
#include "BufferContainer.h"

class UClientConnector :
	public ClientConnector
{
public:
	UClientConnector(void);
	~UClientConnector(void);
	void SetDataHanler(DataHandler * dataHandler)
	{
		dataHandler_ = dataHandler;
	}
	void HandleOutput(UdpBuffer & bufferSend);
protected:
	virtual int ProcessOutput();
	virtual int HandleInput();
	void ProcessIncomeData(UdpBuffer & bufferRev);
protected:
	BufferContainer * queueOutput_;
	DataHandler * dataHandler_;
};
