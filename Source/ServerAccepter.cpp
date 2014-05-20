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

ServerAccepter::ServerAccepter(SokectType sokectType, long timeOut):m_bEnabled(true),m_socketType(sokectType),m_timeOut(timeOut)
{
}

ServerAccepter::ServerAccepter(string localHost,
								int localPort,
								SokectType sokectType,
								long timeOut):m_bEnabled(true),m_socketType(sokectType),m_timeOut(timeOut)
{
	Initialize(localHost, localPort);
}

ServerAccepter::~ServerAccepter(void)
{
	SocketXO::StopService();
}

void ServerAccepter::SetEnable(bool bEnabled)
{
	m_bEnabled = bEnabled;
}

void ServerAccepter::ThreadEntryPoint()
{
	int ret = 0;
	int iErrorCode = 0;

	while(m_bEnabled)
	{
		if (IsReadable(m_socket->GetSocket(),&iErrorCode,m_timeOut))
		{
			ret = HandleInput();
			if (ret <= 0)
			{
				break;
			}
		}
	}
}

void ServerAccepter::Initialize(string localHost,
								int localPort)
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
}
