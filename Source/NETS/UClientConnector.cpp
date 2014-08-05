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
#include "UClientConnector.h"

UClientConnector::UClientConnector(void)
{
	dataHandler_ = NULL;
	socketType_ = SOCKET_TYPE_UDP;
	queueOutput_ = new BufferContainer();
}

UClientConnector::~UClientConnector(void)
{
	delete queueOutput_;
}

int UClientConnector::ProcessOutput()
{
	UdpBuffer bufferSend;
	int len = 0;
	while(queueOutput_->DeQueue(&bufferSend))
	{
		len = ((UdpSocketXO *)socket_)->SendTo(bufferSend);

#if LIB_REACTOR_DEBUG
		static int index = 0;
		printf("(%d) send to (%s:%d) :%d\n",index++, bufferSend.sockAddr.strAddress,bufferSend.sockAddr.port,bufferSend.buffer.length);
#endif
	}
	return len;
}

int UClientConnector::HandleInput()
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
		ProcessIncomeData(bufferRev);
	}

	return bufferRev.buffer.length;
}

void UClientConnector::ProcessIncomeData(UdpBuffer & bufferRev)
{
#if LIB_REACTOR_DEBUG
	static int index = 0;
	printf("(%d) Rev from (%s:%d) :%s\n",index++, bufferRev.sockAddr.strAddress,bufferRev.sockAddr.port,bufferRev.buffer.message);
#endif
	if(dataHandler_!=NULL)
	{
		dataHandler_->DataHanle(bufferRev);
	}
}
void UClientConnector::HandleOutput(UdpBuffer & bufferSend)
{
	if(bufferSend.buffer.length > 0)
	{
		queueOutput_->EnQueue(bufferSend);
	}
}