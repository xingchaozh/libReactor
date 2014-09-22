#pragma once

#include "../Source/IFS/IFS.h"
#include "../Source/IFS/ReflectionX.h"

class ServerDemo :
	public UServerBase
{
public:
	ServerDemo(void);
	~ServerDemo(void);
public:
	void Start(string localServerHost, int localServerPort);
};

class UdpServerDataHandler :
	public UServerDataHandler
{
public:
	UdpServerDataHandler();
	virtual ~UdpServerDataHandler(void);
public:
	void DataHanle(UdpBuffer & udpBuffer);
};

