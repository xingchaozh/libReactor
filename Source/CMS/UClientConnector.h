#pragma once

#include "ClientConnector.h"

#include "LockFreeQueue.h"
#include "../IFS/DataHandler.h"

namespace libReactor
{
	class BufferContainer;
	class UClientConnector :
		public ClientConnector
	{
	public:
		UClientConnector(void);
		~UClientConnector(void);
		void SetDataHanler(DataHandler * dataHandler)
		{
			dataHandler_ = dataHandler;
		}
		bool HandleOutput(UdpBuffer & bufferSend);
	protected:
		virtual int ProcessOutput();
		virtual int HandleInput();
		void ProcessIncomeData(UdpBuffer & bufferRev);
	protected:
		BufferContainer * queueOutput_;
		DataHandler * dataHandler_;
	};
}
