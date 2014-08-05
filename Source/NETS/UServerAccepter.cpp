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
#include "UServerAccepter.h"

UServerAccepter::UServerAccepter()
{
	socketType_ = SOCKET_TYPE_UDP;
}

UServerAccepter::~UServerAccepter(void)
{
}

int UServerAccepter::HandleInput()
{
	char * ptr = (char *)&(bufferRev_.buffer.message);

	bufferRev_.buffer.length = ((UdpSocketXO *)socket_)->RecvFrom(bufferRev_);

	if(SOCKET_ERROR == bufferRev_.buffer.length)
	{
		return SOCKET_ERROR;
	}
	else if(0 == bufferRev_.buffer.length)
	{
		return 0;
	}
	else
	{
		//Process the income data
		ProcessData(bufferRev_);
	}

	return bufferRev_.buffer.length;
}

void UServerAccepter::ProcessData(UdpBuffer & bufferRev)
{
	if(!bufferListRev_.EnQueue(bufferRev))
	{
		printf("UdpServerAccepter::ProcessData():EnQueue Error!\n");
	}
	this->Notify();
}

BufferContainer * UServerAccepter::GetInputBufferQueue()
{
	return &bufferListRev_;
}

bool UServerAccepter::ProcessOutput()
{
	while (bufferListSend_.DeQueue(&bufferSend_))
	{
#if LIB_REACTOR_DEBUG
		static int index = 0;
		printf("(%d) send to (%s:%d) :%d\n",index++, bufferSend_.sockAddr.strAddress,bufferSend_.sockAddr.port,bufferSend_.buffer.length);
#endif
		((UdpSocketXO *)socket_)->SendTo(bufferSend_);
	}
	return true;
}

bool UServerAccepter::HandleOutput(UdpBuffer & udpBuffer)
{
	if(!bufferListSend_.EnQueue(udpBuffer))
	{
		printf("UdpServerAccepter::HandleOutput():EnQueue Error!\n");
		return true; 
	}
	return false;
}