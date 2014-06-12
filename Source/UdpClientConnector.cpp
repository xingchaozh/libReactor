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
	dataHandler_ = NULL;
	socketType_ = SOCKET_TYPE_UDP;
	queueOutput_ = new LockFreeQueue<UdpBuffer>();
}

UdpClientConnector::~UdpClientConnector(void)
{
	delete queueOutput_;
}

int UdpClientConnector::HandleOutput()
{
	UdpBuffer bufferSend;
	int len = 0;
	while(GetOutputBufferQueue()->DeQueue(&bufferSend))
	{
		len = ((UdpSocketXO *)socket_)->SendTo(bufferSend);
#if LIB_REACTOR_DEBUG
		printf("send len = %d\n",len);
#endif
	}
	return len;
}

int UdpClientConnector::HandleInput()
{
	UdpBuffer bufferRev;
	memset(&bufferRev,0,sizeof(UdpBuffer));
	char * ptr = (char *)&(bufferRev.buffer.message);

	bufferRev.buffer.length = ((UdpSocketXO *)socket_)->RecvFrom(bufferRev);

	if(SOCKET_ERROR == bufferRev.buffer.length)
	{
		return SOCKET_ERROR;
	}
	else if(0 == bufferRev.buffer.length)
	{
		return 0;
	}
	else
	{
		//Process the income data
		ProcessData(bufferRev);
	}

	return bufferRev.buffer.length;
}

void UdpClientConnector::ProcessData(UdpBuffer & bufferRev)
{
#if LIB_REACTOR_DEBUG
	static int index = 0;
	printf("(%d) Rev msg from (%s:%d) :%s\n",index++, bufferRev.sockAddr.strAddress,bufferRev.sockAddr.port,bufferRev.buffer.message);
#endif
	if(dataHandler_!=NULL)
	{
		dataHandler_->DataHanle(bufferRev);
	}
}

LockFreeQueue<UdpBuffer> * UdpClientConnector::GetOutputBufferQueue()
{
	return queueOutput_;
}
