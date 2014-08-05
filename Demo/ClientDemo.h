#pragma once

#define _WINSOCKAPI_
#include <winsock2.h>

#include "../Source/NETS/UClientConnector.h"

#include <string>
using namespace std;

class ClientDemo
{
public:
	ClientDemo(void);
	~ClientDemo(void);
public:
	void Start(string localClientHost,
		int localClientPort,
		string remoteServerHost,
		int remoteServerPort);
public:
	SOCKET clientSocket_;
protected:
	UClientConnector * udpClientConnector_;
};

