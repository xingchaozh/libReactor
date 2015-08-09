#pragma once

#include "../../Source/IFS/IFS.h"
#include "../../Source/IFS/ReflectionX.h"

using namespace libReactor;

class EchoClient :
	public UClientBase
{
public:
	void Start(string localClientHost, int localClientPort, string remoteServerHost, int remoteServerPort);
};

class UdpClientDataHandler :
	public UClientDataHandler
{
public:
	void DataHanle(UdpBuffer & udpBuffer);
};

