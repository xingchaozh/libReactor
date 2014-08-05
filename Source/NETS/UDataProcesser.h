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
#include "../IF/IFS.h"
#include "../IF/DataHandler.h"
#include "../IF/Observer.h"

#include "UServerAccepter.h"

class UDataProcesser :
	public Observer, public ThreadX
{
public:
	UDataProcesser();
	UDataProcesser(UServerAccepter * myServerAccepter);
	virtual ~UDataProcesser();
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
	virtual void Update(Subject * sub);

private:
	UServerAccepter * udpServerAccepter_;
	EventXO * threadEventNewData_;
	bool enabled_;
	DataHandler * dataHandler_;
};

