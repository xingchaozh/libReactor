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

UServerAccepter::UServerAccepter(bool serverServiceEnabled)
{
	socketType_ = SOCKET_TYPE_UDP;
	bufferListSend_ = NULL;
	serverService_ = NULL;
	serverServiceEnabled_ = serverServiceEnabled;
}

UServerAccepter::~UServerAccepter(void)
{
	if(NULL != bufferListSend_)
	{
		delete bufferListSend_;
	}
	if(NULL != serverService_)
	{
		serverService_->SetEnabled(false);
	}//serverService_
}

int UServerAccepter::HandleInput()
{
	//printf("UServerAccepter::HandleInput():Notify!\n");
	this->Notify();
	return 1;
}

bool UServerAccepter::ProcessOutput()
{
	if(!serverServiceEnabled_ && bufferListSend_)
	{
		while (bufferListSend_->DeQueue(&bufferSend_))
		{
	#if 0//DEBUG_X
			static int index = 0;
			printf("(%d) send to (%s:%d) :%d\n",index++, bufferSend_.sockAddr.strAddress,bufferSend_.sockAddr.port,bufferSend_.buffer.length);
	#endif
			((UdpSocketXO *)socket_)->SendTo(bufferSend_);
		}
	}
	return true;
}

bool UServerAccepter::HandleOutput(UdpBuffer & udpBuffer)
{
	bool result = true;
	if(!serverServiceEnabled_)
	{
		if(NULL == bufferListSend_)
		{
			bufferListSend_ = new BufferContainer();
		}
		if(!bufferListSend_->EnQueue(udpBuffer))
		{
			printf("UdpServerAccepter::HandleOutput():EnQueue Error!\n");
			result = false; 
		}
	}
	else
	{
		if(NULL == serverService_)
		{
			serverService_ = new UServerService(socket_);
			serverService_->Start();
		}
		result = serverService_->HandleOutput(udpBuffer);
	}
	return result;
}

int UServerAccepter::RetrieveData(UdpBuffer & bufferRev)
{
	return ((UdpSocketXO *)socket_)->RecvFrom(bufferRev);
}

