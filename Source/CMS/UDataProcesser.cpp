/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : UdpDataProcesser.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "UDataProcesser.h"

UDataProcesser::UDataProcesser(UBufferContainer * bufferContainer):enabled_(true),dataHandler_(NULL)
{
	bufferContainer_ = bufferContainer;
	bufferContainer_->Attach(this);

	threadEventNewData_ = new EventXO();
}

UDataProcesser::~UDataProcesser(void)
{
}

void UDataProcesser::Update(Subject * sub)
{
	//printf("UDataProcesser::Update!\n");
	threadEventNewData_->SetEventX();
}

void UDataProcesser::ProcessData(UdpBuffer & bufferRev)
{
	//printf("UDataProcesser::ProcessData!\n");
#if 0//DEBUG_X
	static int index = 0;
	printf("(%d) %d Rev msg from (%s:%d) : length:%d\n",index++,this->GetThreadId(),bufferRev.sockAddr.strAddress,bufferRev.sockAddr.port,bufferRev.buffer.length);
#endif
	if(dataHandler_!=NULL)
	{
		dataHandler_->DataHanle(bufferRev);
	}
	//char buffer[]="Ack from server.";
	//((UdpSocketXO *)udpServerAccepter_->GetUdpSocket())->SendTo(buffer,strlen(buffer),(sockaddr *)&(bufferRev.sockAddr),sizeof(bufferRev.sockAddr));
}

void UDataProcesser::ThreadEntryPoint()
{
	while (enabled_)
	{
		threadEventNewData_->WaitEvent();

		UdpBuffer bufferRev;
		while(bufferContainer_->DeQueue(&bufferRev))
		{
			ProcessData(bufferRev);
		}
	}
}

void UDataProcesser::SetEnable(bool bEnabled)
{
	enabled_ = bEnabled;
}
