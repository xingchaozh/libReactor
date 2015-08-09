#pragma once

#include "LockFreeQueue.h"

namespace libReactor
{
	class LIB_REACTOR_API BufferContainer
	{
	public:
		BufferContainer(UINT16 buffer_size = MAX_SIZE_OF_RING_BUFFER);
		~BufferContainer();

		virtual bool EnQueue(const UdpBuffer & udpBuffer);

		bool DeQueue(UdpBuffer * udpBuffer);

		bool IsEmpty();
	private:
		LockFreeQueue<UdpBuffer> * queue_;
	};
}
