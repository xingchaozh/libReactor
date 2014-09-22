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
#include "../IFS/Subject.h"

#include "buffercontainer.h"

#include "BlockingQueue.h"
class UServerService :
	public SvcHandler
{
public:
	UServerService(SocketXO * socket):
		enabled_(true)
	{
		socket_ = socket;
	}

	virtual ~UServerService()
	{
	}

public:
	bool HandleOutput(UdpBuffer & udpBuffer)
	{
		blockingQueue_.Put(udpBuffer);
		return true;
	}

	void SetEnabled(bool enabled)
	{
		enabled_ = enabled;
	}

private:
	virtual void ThreadEntryPoint()
	{
		while(enabled_)
		{
			blockingQueue_.Take(&bufferSend_);
			((UdpSocketXO *)socket_)->SendTo(bufferSend_);
		}
	}

private:
	bool enabled_;//whether the thread is enabled
	BlockingQueue<UdpBuffer> blockingQueue_;
	UdpBuffer bufferSend_;
	SocketXO * socket_;
};

class UServerAccepter :
	public ServerAccepter, public Subject
{
public:
	UServerAccepter(bool serverServiceEnabled = true);
	~UServerAccepter(void);

	virtual bool HandleOutput(UdpBuffer & udpBuffer);

	int RetrieveData(UdpBuffer & bufferRev);
protected:
	virtual int HandleInput();
	virtual bool ProcessOutput();
protected:
	//BufferContainer bufferListRev_;
	//UdpBuffer bufferRev_;

	UServerService * serverService_;
	BufferContainer * bufferListSend_;
	UdpBuffer bufferSend_;
};



