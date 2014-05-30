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

ClientConnector::ClientConnector(SokectType sokectType, long timeOut):m_bEnabled(true),m_socketType(sokectType),m_timeOut(timeOut)
{
}

ClientConnector::~ClientConnector(void)
{
	SocketXO::StopService();
}

void ClientConnector::SetEnable(bool bEnabled)
{
	m_bEnabled = bEnabled;
}

void ClientConnector::ThreadEntryPoint()
{
	while(m_bEnabled)
	{
		HandleOutput();

		int iErrorCode = 0;
		if(SocketXO::IsReadable(m_socket->GetSocket(),&iErrorCode,m_timeOut))
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
	switch (m_socketType)
	{
	case SOCKET_TYPE_TCP:
		m_socket = new TcpSocketXO();
		((TcpSocketXO *)m_socket)->Create();
		break;
	case SOCKET_TYPE_UDP:
		m_socket = new UdpSocketXO();
		((UdpSocketXO *)m_socket)->Create();
		break;
	default:
		break;
	}
	m_socket->Bind((sockaddr*)&(SocketXO::GetSockAddr(localHost,localPort)));
	m_serverAddr = SocketXO::GetSockAddr(remoteHost,remotePort);
}

sockaddr_in ClientConnector::GetServerAddr()
{
	return m_serverAddr;
}
