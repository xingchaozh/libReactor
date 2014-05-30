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
	UdpServerAccepter(UdpSocketXO * socket);
	~UdpServerAccepter(void);
	LockFreeQueue *  GetBufferQueue();
protected:
	virtual int HandleInput();
	virtual void ProcessData(UdpBufferRev & bufferRev);
protected:
	LockFreeQueue * m_queue;
};
