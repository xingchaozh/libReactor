#pragma once

#include "../Common/Common.h"

namespace libReactor
{
	class UClientBase;
	class LIB_REACTOR_API UClient
	{
	public:
		UClient(void);
		virtual ~UClient(void);
	public:
		void Execute(string localClientHost, int localClientPort, string dataHandlerClassName);
		void HandleOutput(UdpBuffer & bufferSend);

		SocketAddr GetServerAddress(UINT32 index);
		bool AppendServerAddress(SocketAddr & addr);
	protected:
		UClientBase * m_clientBase;
	};
}
