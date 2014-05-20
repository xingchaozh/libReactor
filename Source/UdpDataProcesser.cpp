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
	m_hThreadEventNewData = new EventXO();
	m_bEnabled = true;
}

UdpDataProcesser::UdpDataProcesser(UdpServerAccepter * udpServerAccepter)
{
	m_udpServerAccepter = udpServerAccepter;
	m_udpServerAccepter->Attach(this);

	m_hThreadEventNewData = new EventXO();
}

UdpDataProcesser::~UdpDataProcesser(void)
{
}

void UdpDataProcesser::Update(SubjectX * sub)
{
	m_hThreadEventNewData->SetEventX();
}

void UdpDataProcesser::ProcessData(UdpBufferRev * bufferRev)
{
	static int index = 0;

#if LIB_REACTOR_DEBUG
	printf("(%d) %d Rev msg from (%s:%d) : length:%d\n",index++,this->GetThreadId(),inet_ntoa(bufferRev->fromAddr.sin_addr),bufferRev->fromAddr.sin_port,bufferRev->bufferRev.length);
#endif
	char buffer[]="Ack from server.";
	((UdpSocketXO *)m_udpServerAccepter->GetUdpSocket())->SendTo(buffer,strlen(buffer),(sockaddr *)&(bufferRev->fromAddr),sizeof(bufferRev->fromAddr));
}

void UdpDataProcesser::ThreadEntryPoint()
{
	while (m_bEnabled)
	{
		m_hThreadEventNewData->WaitEvent();

		UdpBufferRev bufferRev;
		while(m_udpServerAccepter->GetBufferQueue()->DeQueue(&bufferRev) >= 0)
		{
			ProcessData(&bufferRev);
		}
	}
}
