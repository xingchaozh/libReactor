#pragma once

#include "../../Source/IFS/IFS.h"
using namespace libReactor;

class EchoServerDemo :
	public UServerBase
{
public:
	void Start(string localServerHost, int localServerPort);
};

class UdpServerDataHandler :
	public UServerDataHandler
{
public:
	void DataHanle(UdpBuffer & udpBuffer);
};
