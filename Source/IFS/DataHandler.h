#pragma once

#include "../Common/DllCommon.h"
#include "../Common/Common.h"

namespace libReactor
{
	class LIB_REACTOR_API DataHandler
	{
	public:
		DataHandler(){}
	public:
		virtual void DataHanle(UdpBuffer & udpBuffer) = 0;
	};
}
