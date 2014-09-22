/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : UDataReader.h
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
#include "../IFS/Observer.h"

#include "UServerAccepter.h"

class UDataReader :
	public Observer, public ThreadX
{
public:
	UDataReader(UServerAccepter * udpServerAccepter);
	virtual ~UDataReader(void);
	void Update(Subject * sub);
	virtual void ThreadEntryPoint();
	int Read();
	void SetBufferListRev(BufferContainer * bufferListRev);
	void SetEnable(bool bEnabled);
protected:
	BufferContainer * bufferListRev_;
	UdpBuffer bufferRev_;
private:
	UServerAccepter * udpServerAccepter_;
	EventXO * threadEventNewData_;
	bool enabled_;
};

