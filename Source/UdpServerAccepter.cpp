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
	queue_ = new LockFreeQueue<UdpBufferRev>();
}

UdpServerAccepter::UdpServerAccepter(UdpSocketXO * socket)
{
	socketType_ = SOCKET_TYPE_UDP;
	queue_ = new LockFreeQueue<UdpBufferRev>();

	SetUdpSocket(socket);
}

UdpServerAccepter::~UdpServerAccepter(void)
{
	delete queue_;
}

int UdpServerAccepter::HandleInput()
{
	struct sockaddr_in tmpAddr;
	int tmpAddrLen = sizeof(tmpAddr);

	UdpBufferRev bufferRev;
	char * ptr = (char *)&(bufferRev.bufferRev.buffer);

	bufferRev.bufferRev.length = ((UdpSocketXO *)socket_)->RecvFrom(ptr,MAX_DGRAM_BUFFER_SIZE,(sockaddr *)&tmpAddr,&tmpAddrLen);

	if(SOCKET_ERROR == bufferRev.bufferRev.length)
	{
		return SOCKET_ERROR;
	}
	else if(0 == bufferRev.bufferRev.length)
	{
		return 0;
	}
	else
	{
		//Process the income data
		bufferRev.fromAddr = tmpAddr;
		ProcessData(bufferRev);
	}

	return bufferRev.bufferRev.length;
}

void UdpServerAccepter::ProcessData(UdpBufferRev & bufferRev)
{
	//for(int i = 0;i<8;i++)//just for test
	if(!queue_->EnQueue(bufferRev))
	{
		printf("EnQueue Error!\n");
	}
	this->Notify();
}

LockFreeQueue<UdpBufferRev> * UdpServerAccepter::GetBufferQueue()
{
	return queue_;
}
