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

#include "../Common/Common.h"

#include "serveraccepter.h"
#include "../IF/Subject.h"

#include "buffercontainer.h"

class UServerAccepter :
	public ServerAccepter, public Subject
{
public:
	UServerAccepter();
	~UServerAccepter(void);
	BufferContainer *  GetInputBufferQueue();
	virtual bool HandleOutput(UdpBuffer & udpBuffer);
protected:
	virtual int HandleInput();
	virtual bool ProcessOutput();
	virtual void ProcessData(UdpBuffer & bufferRev);
protected:
	BufferContainer bufferListRev_;
	UdpBuffer bufferRev_;

	BufferContainer bufferListSend_;
	UdpBuffer bufferSend_;
};
