/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : UdpServerAccepter.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "UdpServerAccepter.h"

UdpServerAccepter::UdpServerAccepter()
{
	socketType_ = SOCKET_TYPE_UDP;
	queueInput_ = new LockFreeQueue<UdpBuffer>();
}

UdpServerAccepter::~UdpServerAccepter(void)
{
	delete queueInput_;
}

int UdpServerAccepter::HandleInput()
{
	UdpBuffer bufferRev;
	char * ptr = (char *)&(bufferRev.buffer.message);

	bufferRev.buffer.length = ((UdpSocketXO *)socket_)->RecvFrom(bufferRev);

	if(SOCKET_ERROR == bufferRev.buffer.length)
	{
		return SOCKET_ERROR;
	}
	else if(0 == bufferRev.buffer.length)
	{
		return 0;
	}
	else
	{
		//Process the income data
		ProcessData(bufferRev);
	}

	return bufferRev.buffer.length;
}

void UdpServerAccepter::ProcessData(UdpBuffer & bufferRev)
{
	//for(int i = 0;i<8;i++)//just for test
	if(!queueInput_->EnQueue(bufferRev))
	{
		printf("EnQueue Error!\n");
	}
	this->Notify();
}

LockFreeQueue<UdpBuffer> * UdpServerAccepter::GetInputBufferQueue()
{
	return queueInput_;
}
