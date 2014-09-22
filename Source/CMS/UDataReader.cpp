/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : UDataReader.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "UDataReader.h"


UDataReader::UDataReader(UServerAccepter * udpServerAccepter)
{
	udpServerAccepter_ = udpServerAccepter;
	udpServerAccepter_->Attach(this);

	threadEventNewData_ = new EventXO();
	enabled_ = true;

	bufferListRev_ = NULL;
}


UDataReader::~UDataReader(void)
{
}

void UDataReader::Update(Subject * sub)
{
	threadEventNewData_->SetEventX();
}

void UDataReader::ThreadEntryPoint()
{
	while (enabled_)
	{
		threadEventNewData_->WaitEvent();
		Read();
	}
}

int UDataReader::Read()
{
	//printf("UDataReader::Read():Read!\n");
	char * ptr = (char *)&(bufferRev_.buffer.message);

	bufferRev_.buffer.length = udpServerAccepter_->RetrieveData(bufferRev_);

	if(SOCKET_ERROR == bufferRev_.buffer.length)
	{
		return SOCKET_ERROR;
	}
	else if(0 == bufferRev_.buffer.length)
	{
		return 0;
	}
	else
	{
		//EnQueue the income data
		if(NULL != bufferListRev_)
		{
			bufferListRev_->EnQueue(bufferRev_);
		}
	}

	return bufferRev_.buffer.length;
}

void UDataReader::SetBufferListRev(BufferContainer * bufferListRev)
{
	bufferListRev_ = bufferListRev;
}

void UDataReader::SetEnable(bool bEnabled)
{
	enabled_ = bEnabled;
}