/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : UdpServerAccepter.h
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

#include "CommonX.h"

#include "serveraccepter.h"
#include "SubjectX.h"

#include "LockFreeQueues.h"

class UdpServerAccepter :
	public ServerAccepter, public SubjectX
{
public:
	UdpServerAccepter();
	~UdpServerAccepter(void);
	LockFreeQueue<UdpBuffer> *  GetInputBufferQueue();
protected:
	virtual int HandleInput();
	virtual void ProcessData(UdpBuffer & bufferRev);
protected:
	LockFreeQueue<UdpBuffer> * queueInput_;
};
