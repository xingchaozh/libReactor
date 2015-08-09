#include "UClientBase.h"

#include "UClientConnector.h"
#include "UClientDataHandler.h"

#include "../IFS/ReflectionX.h"

namespace libReactor
{
	UClientBase::UClientBase(void)
	{
		udpClientConnector_ = NULL;
		dataHandler_ = NULL;
	}

	UClientBase::~UClientBase(void)
	{
		Destroy();
	}

	void UClientBase::Execute(string localClientHost,
		int localClientPort,
		string dataHandlerClassName)
	{
		udpClientConnector_ = new UClientConnector();
		if (SOCKET_ERROR != udpClientConnector_->Initialize(localClientHost, localClientPort))
		{
			udpClientConnector_->SetTimeOut(50);
			dataHandler_ = (UClientDataHandler *)ReflectionClassFactory::GetClassByName(dataHandlerClassName);
			udpClientConnector_->SetDataHanler(dataHandler_);
			udpClientConnector_->Start();
		}
		else
		{
			printf("UClientBase::Execute: Failed!\n");
			delete udpClientConnector_;
			udpClientConnector_ = NULL;
		}
	}

	void UClientBase::Destroy()
	{
		if (NULL != udpClientConnector_)
		{
			udpClientConnector_->SetEnable(false);
			udpClientConnector_->Join();
			delete udpClientConnector_;
			udpClientConnector_ = NULL;
		}

		if (NULL != dataHandler_)
		{
			delete dataHandler_;
			dataHandler_ = NULL;
		}
	}

	void UClientBase::HandleOutput(UdpBuffer & bufferSend)
	{
		if (NULL != udpClientConnector_)
		{
			udpClientConnector_->HandleOutput(bufferSend);
		}
	}

	SocketAddr UClientBase::GetServerAddress(UINT32 index)
	{
		SocketAddr addr;
		memset(&addr, 0, sizeof(SocketAddr));
		if (index < vecSocketAddrs_.size())
		{
			return vecSocketAddrs_[index];
		}
		return addr;
	}

	bool UClientBase::AppendServerAddress(SocketAddr & addr)
	{
		bool result = true;
		vecSocketAddrs_.push_back(addr);
		return result;
	}
}


