#pragma once

#include "../Source/IF/IFS.h"
#include "../Source/IF/DataHandler.h"
#include "../Source/NETS/UServerAccepter.h"

class UdpServerDataHandler :
	public DataHandler
{
public:
	UdpServerDataHandler(UServerAccepter * udpServerAccepter);
	virtual ~UdpServerDataHandler(void);
public:
	void DataHanle(UdpBuffer & udpBuffer);
protected:
	UServerAccepter * udpServerAccepter_;
};

