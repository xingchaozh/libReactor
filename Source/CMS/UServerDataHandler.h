/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : UServerDataHandler.h
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
#include "UServerAccepter.h"

class UServerDataHandler :
	public DataHandler
{
public:
	UServerDataHandler(void);
	virtual ~UServerDataHandler(void);
public :
	virtual void DataHanle(UdpBuffer & udpBuffer) = 0;

	void SetServerAccepter(UServerAccepter * udpServerAccepter)
	{
		udpServerAccepter_ = udpServerAccepter;
	}

	bool HandleOutput(UdpBuffer & udpBuffer)
	{
		bool result = false;
		if (NULL != udpServerAccepter_)
		{
			result = udpServerAccepter_->HandleOutput(udpBuffer);
		}
		return result;
	}
protected:
	UServerAccepter * udpServerAccepter_;
};

