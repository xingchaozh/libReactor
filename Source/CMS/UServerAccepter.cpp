/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : Ida
* Filename      : UdpServerAccepter.cpp
* Version       : V1.0
* Programmer(s) : XXX
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "UServerAccepter.h"
namespace libReactor
{
//////////////////////////////////////////////////////////////////////////
//UServerAccepter
//////////////////////////////////////////////////////////////////////////
UServerAccepter::UServerAccepter()
{
	socketType_ = SOCKET_TYPE_UDP;
	serverService_ = NULL;
}

UServerAccepter::~UServerAccepter(void)
{
	if(!serverService_)
	{
		serverService_->SetEnabled(false);
	}
}

int UServerAccepter::HandleInput()
{
	this->Notify();
	return 1;
}

bool UServerAccepter::HandleOutput(UdpBuffer & udpBuffer)
{
	if(!serverService_)
	{
		serverService_ = new UServerOutputService(socket_);
		serverService_->Start();
	}
	return serverService_->HandleOutput(udpBuffer);
}

int UServerAccepter::RetrieveData(UdpBuffer & bufferRev)
{
	std::lock_guard<std::mutex> lock(m_mutexRead);
	return ((UdpSocket *)socket_)->RecvFrom(bufferRev);
}


//////////////////////////////////////////////////////////////////////////
//UServerOutputService
//////////////////////////////////////////////////////////////////////////
UServerOutputService::UServerOutputService(SocketX * socket):
	enabled_(true)
{
	socket_ = socket;
}

UServerOutputService::~UServerOutputService()
{
}

bool UServerOutputService::HandleOutput(UdpBuffer & udpBuffer)
{
	blockingQueue_.Put(udpBuffer);
	return true;
}

void UServerOutputService::SetEnabled(bool enabled)
{
	enabled_ = enabled;
}

void UServerOutputService::ThreadEntryPoint()
{
	while(enabled_)
	{
		blockingQueue_.Take(&bufferSend_);
		((UdpSocket *)socket_)->SendTo(bufferSend_);
	}
}
}