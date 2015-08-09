#pragma once

#include "../Common/Common.h"

#include <vector>
using namespace std;

namespace libReactor
{
	class UClientConnector;
	class UClientDataHandler;
	class UClientBase
	{
	public:
		UClientBase(void);
		virtual ~UClientBase(void);
	public:
		void Execute(string localClientHost,
			int localClientPort,
			string dataHandlerClassName);

		void HandleOutput(UdpBuffer & bufferSend);
		SocketAddr GetServerAddress(UINT32 index);
		bool AppendServerAddress(SocketAddr & addr);

	protected:
		void Destroy();

	protected:
		UClientConnector * udpClientConnector_;
		UClientDataHandler * dataHandler_;
		vector<SocketAddr> vecSocketAddrs_;
	};
}
