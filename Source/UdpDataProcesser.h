/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : UdpDataProcesser.h
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
#include "observerx.h"
#include "UdpServerAccepter.h"
#include "threadx.h"

#include "EventXO.h"

#include "DataHandler.h"

class UdpDataProcesser :
	public ObserverX, public ThreadX
{
public:
	UdpDataProcesser(void);
	UdpDataProcesser(UdpServerAccepter * myServerAccepter);
	~UdpDataProcesser(void);
	void SetEnable(bool bEnabled)
	{
		enabled_ = bEnabled;
	}
	void SetDataHanler(DataHandler * dataHandler)
	{
		dataHandler_ = dataHandler;
	}
protected:

	void ProcessData(UdpBuffer & bufferRev);
	virtual void ThreadEntryPoint();
	virtual void Update(SubjectX * sub);

private:
	UdpServerAccepter * udpServerAccepter_;
	EventXO * threadEventNewData_;
	bool enabled_;
	DataHandler * dataHandler_;
};

