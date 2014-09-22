/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : UClientBase.h
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#pragma once

#include "UClientConnector.h"
#include "UClientDataHandler.h"

#include <vector>
using namespace std;

class UClientBase
{
public:
	UClientBase(void);
	virtual ~UClientBase(void);
public:
	void Execute(string localClientHost,
		int localClientPort,
		string dataHandlerClassName);
	
	void HandleOutput(UdpBuffer & bufferSend);
	SocketAddr GetServerAddress(UINT32 index);
	bool AppendServerAddress(SocketAddr & addr);

	void WartForExit();
	void Destroy();
protected:
	UClientConnector * udpClientConnector_;
	UClientDataHandler * dataHandler_;
	vector<SocketAddr> vecSocketAddrs_;
};

