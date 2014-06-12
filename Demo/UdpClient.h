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
	UdpClient(void);
	~UdpClient(void);
public:
	void Start(string localClientHost,
		int localClientPort,
		string remoteServerHost,
		int remoteServerPort);
public:
	SOCKET clientSocket_;
protected:
	UdpClientConnector * udpClientConnector_;
};

