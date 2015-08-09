#include "BufferContainer.h"

namespace libReactor
{
	BufferContainer::BufferContainer(UINT16 buffer_size)
	{
		queue_ = new LockFreeQueue<UdpBuffer>(buffer_size);
	}

	BufferContainer::~BufferContainer()
	{
		delete queue_;
	}

	bool BufferContainer::EnQueue(const UdpBuffer & udpBuffer)
	{
		return queue_->EnQueue(udpBuffer);
	}

	bool BufferContainer::DeQueue(UdpBuffer * udpBuffer)
	{
		return queue_->DeQueue(udpBuffer);
	}

	bool BufferContainer::IsEmpty()
	{
		return queue_->IsEmpty();
	}
}
