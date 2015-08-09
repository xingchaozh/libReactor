#include "UClientConnector.h"
#include "BufferContainer.h"

namespace libReactor
{
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
		while (queueOutput_->DeQueue(&bufferSend))
		{
			len = ((UdpSocket *)socket_)->SendTo(bufferSend);
		}
		return len;
	}

	int UClientConnector::HandleInput()
	{
		UdpBuffer bufferRev;
		memset(&bufferRev, 0, sizeof(UdpBuffer));
		char * ptr = (char *)&(bufferRev.buffer.message);

		bufferRev.buffer.length = ((UdpSocket *)socket_)->RecvFrom(bufferRev);

		if (SOCKET_ERROR == bufferRev.buffer.length)
		{
			return SOCKET_ERROR;
		}
		else if (0 == bufferRev.buffer.length)
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
		if (dataHandler_ != NULL)
		{
			dataHandler_->DataHanle(bufferRev);
		}
	}

	bool UClientConnector::HandleOutput(UdpBuffer & bufferSend)
	{
		bool result = false;
		if (bufferSend.buffer.length > 0)
		{
			result = queueOutput_->EnQueue(bufferSend);
		}
		return result;
	}
}
