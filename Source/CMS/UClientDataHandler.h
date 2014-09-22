/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : UClientDataHandler.h
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

#include "..\ifs\datahandler.h"
#include "UClientConnector.h"

class UClientDataHandler :
	public DataHandler
{
public:
	UClientDataHandler(void);
	virtual ~UClientDataHandler(void);
public :
	virtual void DataHanle(UdpBuffer & udpBuffer) = 0;

	void SetUClientConnector(UClientConnector * udpClientConnector)
	{
		udpClientConnector_ = udpClientConnector;
	}

	bool HandleOutput(UdpBuffer & udpBuffer)
	{
		bool result = false;
		if (NULL != udpClientConnector_)
		{
			result = udpClientConnector_->HandleOutput(udpBuffer);
		}
		return result;
	}
protected:
	UClientConnector * udpClientConnector_;
};

