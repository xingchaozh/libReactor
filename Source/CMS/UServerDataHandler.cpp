#include "UServerDataHandler.h"
#include "UServerAccepter.h"

namespace libReactor
{
UServerDataHandler::UServerDataHandler(void)
{
}


UServerDataHandler::~UServerDataHandler(void)
{
}

void UServerDataHandler::SetServerAccepter(UServerAccepter * udpServerAccepter)
{
	udpServerAccepter_ = udpServerAccepter;
}

bool UServerDataHandler::HandleOutput(UdpBuffer & udpBuffer)
{
	bool result = false;
	if (NULL != udpServerAccepter_)
	{
		result = udpServerAccepter_->HandleOutput(udpBuffer);
	}
	return result;
}
}
