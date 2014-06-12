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
#include "UdpDataProcesser.h"

UdpDataProcesser::UdpDataProcesser(void)
{
	dataHandler_ = NULL;
	threadEventNewData_ = new EventXO();
	enabled_ = true;
}

UdpDataProcesser::UdpDataProcesser(UdpServerAccepter * udpServerAccepter)
{
	dataHandler_ = NULL;
	udpServerAccepter_ = udpServerAccepter;
	udpServerAccepter_->Attach(this);

	threadEventNewData_ = new EventXO();
}

UdpDataProcesser::~UdpDataProcesser(void)
{
}

void UdpDataProcesser::Update(SubjectX * sub)
{
	threadEventNewData_->SetEventX();
}

void UdpDataProcesser::ProcessData(UdpBuffer & bufferRev)
{
#if LIB_REACTOR_DEBUG
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

void UdpDataProcesser::ThreadEntryPoint()
{
	while (enabled_)
	{
		threadEventNewData_->WaitEvent();

		UdpBuffer bufferRev;
		while(udpServerAccepter_->GetInputBufferQueue()->DeQueue(&bufferRev))
		{
			ProcessData(bufferRev);
		}
	}
}
