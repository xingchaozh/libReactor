#include "UBufferContainer.h"

namespace libReactor
{
	UBufferContainer::UBufferContainer(UINT16 buffer_size)
	{
	}


	UBufferContainer::~UBufferContainer(void)
	{
	}

	bool UBufferContainer::EnQueue(const UdpBuffer & udpBuffer)
	{
		bool result = BufferContainer::EnQueue(udpBuffer);
		this->Notify();
		return result;
	}
}
