#pragma once

#include "../CMS/BufferContainer.h"
#include "../IFS/Subject.h"

namespace libReactor
{
	class UBufferContainer :
		public BufferContainer, public Subject
	{
	public:
		UBufferContainer(UINT16 buffer_size = MAX_SIZE_OF_RING_BUFFER);
		virtual ~UBufferContainer(void);
	public:
		virtual bool EnQueue(const UdpBuffer & udpBuffer);
	};
}
