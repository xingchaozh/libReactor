#include "SocketHelper.h"

namespace libReactor
{
	bool SocketHelper::startupService_ = false;

	SocketHelper::SocketHelper(void)
	{
		StartupService();
	}

	SocketHelper::~SocketHelper(void)
	{
		StopService();
	}

	void SocketHelper::StartupService()
	{
		if (!startupService_)
		{
			WSADATA wsa;
			if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
			{
				printf("WSAStartup() failed!\n");
				return;
			}
			startupService_ = true;
		}
	}

	void SocketHelper::StopService()
	{
		if (startupService_)
		{
			WSACleanup();
			startupService_ = false;
		}
	}

	sockaddr_in SocketHelper::GetStdSockAddr(string localServerHost, int localServerPort)
	{
		struct sockaddr_in localAddr;
		//set protocol family
		localAddr.sin_family = AF_INET;
		//set host port
		localAddr.sin_port = htons(localServerPort);
		//Struct sin_addr is  used to defind IP address,  it's a property of addr_in.
		//It's nest three structs as S_un_b, S_un_w and S-un.(union)
		localAddr.sin_addr.s_addr = inet_addr(localServerHost.c_str());//htonl(INADDR_ANY);
		return localAddr;
	}

	sockaddr_in SocketHelper::GetStdSockAddr(SocketAddr & socketAddr)
	{
		return GetStdSockAddr(socketAddr.strAddress, socketAddr.port);
	}

	SocketAddr SocketHelper::GetSockAddr(sockaddr_in & sockaddr)
	{
		SocketAddr socketAddr;
		memset(&socketAddr, 0, sizeof(SocketAddr));
		socketAddr.port = ntohs(sockaddr.sin_port);
		in_addr * in_addr_ = (in_addr*)(&(sockaddr.sin_addr.s_addr));
		memcpy(socketAddr.strAddress, inet_ntoa(*in_addr_), strlen(inet_ntoa(*in_addr_)));
		return socketAddr;
	}

	SocketAddr SocketHelper::GetSockAddr(string host, int port)
	{
		SocketAddr socketAddr;
		memset(&socketAddr, 0, sizeof(SocketAddr));
		memcpy(socketAddr.strAddress, host.c_str(), host.length());
		socketAddr.port = port;
		return socketAddr;
	}
}
