#pragma once

#include "../Source/IFS/IFS.h"
#include "../Source/IFS/ReflectionX.h"

class ClientDemo :
	public UClientBase
{
public:
	ClientDemo(void);
	virtual ~ClientDemo(void);
public:
	void Start(string localClientHost,
		int localClientPort,
		string remoteServerHost,
		int remoteServerPort);
};

class UdpClientDataHandler :
	public UClientDataHandler
{
public:
	UdpClientDataHandler();
	virtual ~UdpClientDataHandler(void);
public:
	void DataHanle(UdpBuffer & udpBuffer);
};


