#pragma once

#include "../Common/Common.h"

namespace libReactor
{
	class UServerBase;
	class LIB_REACTOR_API UServer
	{
	public:
		UServer(void);
		virtual ~UServer(void);
	public:
		bool SetParameters(UINT16 bufferSize = USERVER_BUFFER_SIZE,
			UINT16 numDataReader = NUM_USERVER_DATA_READER,
			UINT16 numDataProcesser = NUM_USERVER_DATA_PROCESSER,
			long timeOut = USERVER_LISTEN_TIMEOUT);

		void Execute(string localServerHost, int localServerPort, string dataHandlerClassName);

		bool HandleOutput(UdpBuffer & udpBuffer);
	protected:
		UServerBase * m_serverBase;
	};
}
