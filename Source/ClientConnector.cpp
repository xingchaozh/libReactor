/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : ClientConnector.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "ClientConnector.h"

ClientConnector::ClientConnector(SokectType sokectType, long timeOut):enabled_(true),socketType_(sokectType),timeOut_(timeOut)
{
}

ClientConnector::~ClientConnector(void)
{
	SocketXO::StopService();
}

void ClientConnector::SetEnable(bool bEnabled)
{
	enabled_ = bEnabled;
}

void ClientConnector::ThreadEntryPoint()
{
	while(enabled_)
	{
		HandleOutput();

		int iErrorCode = 0;
		if(SocketXO::IsReadable(socket_->GetSocket(),&iErrorCode,timeOut_))
		{
			HandleInput();
		}
	}
}

void ClientConnector::Initialize(string localHost,
								 int localPort,
								 string remoteHost,
								 int remotePort)
{
	SocketXO::StartupService();
	switch (socketType_)
	{
	case SOCKET_TYPE_TCP:
		socket_ = new TcpSocketXO();
		((TcpSocketXO *)socket_)->Create();
		break;
	case SOCKET_TYPE_UDP:
		socket_ = new UdpSocketXO();
		((UdpSocketXO *)socket_)->Create();
		break;
	default:
		break;
	}
	socket_->Bind((sockaddr*)&(SocketXO::GetSockAddr(localHost,localPort)));
	serverAddr_ = SocketXO::GetSockAddr(remoteHost,remotePort);
}

sockaddr_in ClientConnector::GetServerAddr()
{
	return serverAddr_;
}
