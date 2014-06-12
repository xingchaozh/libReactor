#pragma once

#include "../Source/DataHandler.h"
#include "../Source/UdpServerAccepter.h"

class UdpServerDataHandler :
	public DataHandler
{
public:
	UdpServerDataHandler(string localServerHost, int remoteClientPort = 0);
	virtual ~UdpServerDataHandler(void);
public:
	void DataHanle(UdpBuffer & udpBuffer);
	void SetRemotePort(int remotePort);
protected:
	string localServerHost_;
	int remoteClientPort_;
	UdpSocketXO * socket_;
};

