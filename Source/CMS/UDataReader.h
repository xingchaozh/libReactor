#pragma once

#include "../IFS/IFSInternal.h"
#include "../IFS/Observer.h"

namespace libReactor
{
	class BufferContainer;
	class UServerAccepter;
	class UDataReader :
		public Observer, public libReactor::Thread
	{
	public:
		UDataReader(UServerAccepter * udpServerAccepter);
		virtual ~UDataReader(void);
		void Update(Subject * sub);
		virtual void ThreadEntryPoint();
		int Read();
		void SetBufferListRev(BufferContainer * bufferListRev);
		void SetEnable(bool bEnabled);
	protected:
		BufferContainer * bufferListRev_;
		UdpBuffer bufferRev_;
	private:
		UServerAccepter * udpServerAccepter_;
		libReactor::Event * event_;
		bool enabled_;
	};
}
