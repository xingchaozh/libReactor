#include "UClientDataHandler.h"
#include "UClientConnector.h"

namespace libReactor
{
	UClientDataHandler::UClientDataHandler(void)
	{
	}

	UClientDataHandler::~UClientDataHandler(void)
	{
	}

	void UClientDataHandler::SetUClientConnector(UClientConnector * udpClientConnector)
	{
		udpClientConnector_ = udpClientConnector;
	}

	bool UClientDataHandler::HandleOutput(UdpBuffer & udpBuffer)
	{
		bool result = false;
		if (NULL != udpClientConnector_)
		{
			result = udpClientConnector_->HandleOutput(udpBuffer);
		}
		return result;
	}
}
