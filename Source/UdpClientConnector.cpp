/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : UdpClientConnector.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "UdpClientConnector.h"

UdpClientConnector::UdpClientConnector(void)
{
	m_socketType = SOCKET_TYPE_UDP;
	m_queue = new LockFreeQueues();
}

UdpClientConnector::~UdpClientConnector(void)
{
	delete m_queue;
}

int UdpClientConnector::HandleOutput()
{
	UdpBufferRev bufferRev;
	int len = 0;
	while(GetBufferQueue()->DeQueue(&bufferRev) >= 0)
	{
		len = ((UdpSocketXO *)m_socket)->SendTo(bufferRev.bufferRev.buffer,bufferRev.bufferRev.length,(sockaddr *)&m_serverAddr,sizeof(m_serverAddr));
	}
	return len;
}

int UdpClientConnector::HandleInput()
{
	struct sockaddr_in tmpAddr;
	int tmpAddrLen = sizeof(tmpAddr);

	UdpBufferRev bufferRev;
	memset(bufferRev.bufferRev.buffer,0,MAX_DGRAM_BUFFER_SIZE);
	char * ptr = (char *)&(bufferRev.bufferRev.buffer);

	bufferRev.bufferRev.length = ((UdpSocketXO *)m_socket)->RecvFrom(ptr,MAX_DGRAM_BUFFER_SIZE,(sockaddr *)&tmpAddr,&tmpAddrLen);

	if(SOCKET_ERROR == bufferRev.bufferRev.length)
	{
		return SOCKET_ERROR;
	}
	else if(0 == bufferRev.bufferRev.length)
	{
		return 0;
	}
	else
	{
		//Process the income data
		bufferRev.fromAddr = tmpAddr;
		ProcessData(&bufferRev);
	}

	return bufferRev.bufferRev.length;
}

void UdpClientConnector::ProcessData(UdpBufferRev * bufferRev)
{
#if LIB_REACTOR_DEBUG
	static int index = 0;
	printf("(%d) Rev msg from (%s:%d) :%s\n",index++, inet_ntoa(bufferRev->fromAddr.sin_addr),bufferRev->fromAddr.sin_port,bufferRev->bufferRev.buffer);
#endif
	//this->Notify();
}

LockFreeQueues * UdpClientConnector::GetBufferQueue()
{
	return m_queue;
}
