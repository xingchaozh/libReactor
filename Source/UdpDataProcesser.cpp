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
	threadEventNewData_ = new EventXO();
	enabled_ = true;
}

UdpDataProcesser::UdpDataProcesser(UdpServerAccepter * udpServerAccepter)
{
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

void UdpDataProcesser::ProcessData(UdpBufferRev * bufferRev)
{
	static int index = 0;

#if LIB_REACTOR_DEBUG
	printf("(%d) %d Rev msg from (%s:%d) : length:%d\n",index++,this->GetThreadId(),inet_ntoa(bufferRev->fromAddr.sin_addr),bufferRev->fromAddr.sin_port,bufferRev->bufferRev.length);
#endif
	char buffer[]="Ack from server.";
	((UdpSocketXO *)udpServerAccepter_->GetUdpSocket())->SendTo(buffer,strlen(buffer),(sockaddr *)&(bufferRev->fromAddr),sizeof(bufferRev->fromAddr));
}

void UdpDataProcesser::ThreadEntryPoint()
{
	while (enabled_)
	{
		threadEventNewData_->WaitEvent();

		UdpBufferRev bufferRev;
		while(udpServerAccepter_->GetBufferQueue()->DeQueue(&bufferRev))
		{
			ProcessData(&bufferRev);
		}
	}
}
