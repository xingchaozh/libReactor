#pragma once

#include "SvcHandler.h"

namespace libReactor
{
	class ServerAccepter :
		public SvcHandler
	{
	public:
		ServerAccepter(SokectType socketType = SOCKET_TYPE_UDP, long timeOut = 100);
		ServerAccepter(string localHost, int localPort, SokectType m_socketType = SOCKET_TYPE_UDP, long timeOut = 1000);
		virtual ~ServerAccepter(void);

	public:
		void Initialize(string localServerHost, int localServerPort);
		void SetEnable(bool bEnabled);
		void SetTimeOut(long timeOut);
	protected:
		virtual int HandleInput() = 0;
		virtual int ProcessInput();
		//virtual bool ProcessOutput() = 0;

	private:
		virtual void ThreadEntryPoint();
	protected:
		SokectType socketType_;
		SocketX * socket_;
		bool enabled_;//whether the thread is enabled
		long timeOut_;//milliseconds
		//bool serverOutputServiceEnabled_;
	};
}
