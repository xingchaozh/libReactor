#pragma once

#include "../Common/Common.h"
#include <string>
using namespace std;

namespace libReactor
{
	class LIB_REACTOR_API SocketHelper
	{
	public:
		SocketHelper(void);
		virtual ~SocketHelper(void);

	public:
		static void StartupService();
		static void StopService();

		static sockaddr_in GetStdSockAddr(string localServerHost, int localServerPort);
		static sockaddr_in GetStdSockAddr(SocketAddr & socketAddr);
		static SocketAddr GetSockAddr(sockaddr_in & sockaddr);
		static SocketAddr GetSockAddr(string host, int port);

	private:
		static bool startupService_;
	};
}

