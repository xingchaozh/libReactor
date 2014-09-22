/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : UServerBase.h
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

#include "UServerAccepter.h"
#include "UDataReader.h"
#include "UDataProcesser.h"
#include "UServerDataHandler.h"
#include <vector>
using namespace std;

class UServerBase
{
public:
	UServerBase(UINT16 bufferSize = USERVER_BUFFER_SIZE, 
		UINT16 numDataReader = NUM_USERVER_DATA_READER, 
		UINT16 unmDataProcesser = NUM_USERVER_DATA_PROCESSER, 
		long timeOut = USERVER_LISTEN_TIMEOUT);
	virtual ~UServerBase(void);

public:
	bool SetParameters(UINT16 bufferSize = USERVER_BUFFER_SIZE, 
		UINT16 numDataReader = NUM_USERVER_DATA_READER, 
		UINT16 numDataProcesser = NUM_USERVER_DATA_PROCESSER, 
		long timeOut = USERVER_LISTEN_TIMEOUT);
	void Execute(string localServerHost, int localServerPort, string dataHandlerClassName, long timeOut = 50);
	

	bool HandleOutput(UdpBuffer & udpBuffer);

	void WaitForExit();
	void Destroy();
protected:
	UServerAccepter * serverAccepter_;
	vector<UDataReader *> vecUDataReader_;
	vector<UDataProcesser *> vecDataProcesser_;
	vector<UServerDataHandler *> vecDataHandler_;
	UBufferContainer * UBufferContainer_;
	bool ServiceStarted_;

private:
	UINT16 bufferSize_;
	UINT16 numDataReader_;
	UINT16 numDataProcesser_;
	long timeOut_;
};

