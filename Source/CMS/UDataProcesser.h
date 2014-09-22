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
#include "../IFS/IFSInternal.h"
#include "../IFS/DataHandler.h"
#include "../IFS/Observer.h"

#include "UBufferContainer.h"

class UDataProcesser :
	public Observer, public ThreadX
{
public:
	UDataProcesser(UBufferContainer * bufferContainer);
	virtual ~UDataProcesser();
	void SetEnable(bool bEnabled);
	void SetDataHanler(DataHandler * dataHandler)
	{
		dataHandler_ = dataHandler;
	}
protected:

	void ProcessData(UdpBuffer & bufferRev);
	virtual void ThreadEntryPoint();
	virtual void Update(Subject * sub);

private:
	UBufferContainer * bufferContainer_;
	EventXO * threadEventNewData_;
	bool enabled_;
	DataHandler * dataHandler_;
};

