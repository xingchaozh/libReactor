#pragma once

#include "../Common/Common.h"
#include "../IFS/Subject.h"

#include "BlockingQueue.h"

#include "SvcHandler.h"
#include "ServerAccepter.h"

#include <mutex>
namespace libReactor
{
	class UServerOutputService;
	class UServerAccepter :
		public ServerAccepter, public Subject
	{
	public:
		UServerAccepter();
		~UServerAccepter(void);

		virtual bool HandleOutput(UdpBuffer & udpBuffer);

		int RetrieveData(UdpBuffer & bufferRev);

	protected:
		virtual int HandleInput();

	protected:
		UServerOutputService * serverService_;
	private:
		std::mutex m_mutexRead;
	};

	class UServerOutputService :
		public SvcHandler
	{
	public:
		UServerOutputService(SocketX * socket);
		virtual ~UServerOutputService();

	public:
		bool HandleOutput(UdpBuffer & udpBuffer);
		void SetEnabled(bool enabled);

	private:
		virtual void ThreadEntryPoint();

	private:
		bool enabled_;//whether the thread is enabled
		BlockingQueue<UdpBuffer> blockingQueue_;
		UdpBuffer bufferSend_;
		SocketX * socket_;
	};
}
