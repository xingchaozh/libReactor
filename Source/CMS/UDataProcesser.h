#pragma once

#include "../IFS/IFSInternal.h"
#include "../IFS/DataHandler.h"
#include "../IFS/Observer.h"

namespace libReactor
{
	class UBufferContainer;
	class UDataProcesser :
		public Observer, public libReactor::Thread
	{
	public:
		UDataProcesser(UBufferContainer * bufferContainer);
		virtual ~UDataProcesser();
		void SetEnable(bool bEnabled);
		void SetDataHanler(DataHandler * dataHandler) { dataHandler_ = dataHandler; }
		virtual void Update(Subject * sub);

	protected:
		void ProcessData(UdpBuffer & bufferRev);
		virtual void ThreadEntryPoint();

	private:
		UBufferContainer * bufferContainer_;
		libReactor::Event * threadEventNewData_;
		bool enabled_;
		DataHandler * dataHandler_;
	};
}
