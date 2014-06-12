/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : ServerAccepter.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "ServerAccepter.h"

ServerAccepter::ServerAccepter(SokectType sokectType, long timeOut):enabled_(true),socketType_(sokectType),timeOut_(timeOut)
{
}

ServerAccepter::ServerAccepter(string localHost,
								int localPort,
								SokectType sokectType,
								long timeOut):enabled_(true),socketType_(sokectType),timeOut_(timeOut)
{
	Initialize(localHost, localPort);
}

ServerAccepter::~ServerAccepter(void)
{
	SocketXO::StopService();
}

void ServerAccepter::SetEnable(bool bEnabled)
{
	enabled_ = bEnabled;
}

void ServerAccepter::ThreadEntryPoint()
{
	int ret = 0;
	int iErrorCode = 0;

	while(enabled_)
	{
		if (socket_->IsReadable(timeOut_))
		{
			ret = HandleInput();
			if (ret <= 0)
			{
				break;
			}
		}
	}
}

void ServerAccepter::Initialize(string localServerHost,
								int localServerPort)
{
	SocketXO::StartupService();
	switch (socketType_)
	{
	case SOCKET_TYPE_TCP:
		socket_ = new TcpSocketXO();
		break;
	case SOCKET_TYPE_UDP:
		socket_ = new UdpSocketXO();
		break;
	default:
		break;
	}
	socket_->Bind(localServerHost,localServerPort);
}

void ServerAccepter::SetTimeOut(long timeOut)
{
	timeOut_ = timeOut;
}