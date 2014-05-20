#pragma once

#define _WINSOCKAPI_
#include <winsock2.h>

#include "../Source/ThreadX.h"
#include "../Source/UdpClientConnector.h"

#include <string>
using namespace std;

class UdpClient
{
public:
	SOCKET m_clientSocket;
public:
	UdpClient(void);
	~UdpClient(void);
public:
	void Start(string localHost,
		int localPort,
		string remoteHost,
		int remotePort);
protected:
	UdpClientConnector * m_udpClientConnector;
};

