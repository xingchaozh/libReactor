#pragma once

#include "../IFS/DataHandler.h"

namespace libReactor
{
	class UServerAccepter;
	class LIB_REACTOR_API UServerDataHandler :
		public DataHandler
	{
	public:
		UServerDataHandler(void);
		virtual ~UServerDataHandler(void);
	public:
		virtual void DataHanle(UdpBuffer & udpBuffer) = 0;

		void SetServerAccepter(UServerAccepter * udpServerAccepter);

		bool HandleOutput(UdpBuffer & udpBuffer);
	protected:
		UServerAccepter * udpServerAccepter_;
	};
}
