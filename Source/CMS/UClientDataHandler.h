#pragma once

#include "../IFS/DataHandler.h"

namespace libReactor
{
	class UClientConnector;
	class LIB_REACTOR_API UClientDataHandler :
		public DataHandler
	{
	public:
		UClientDataHandler(void);
		virtual ~UClientDataHandler(void);
	public:
		virtual void DataHanle(UdpBuffer & udpBuffer) = 0;

		void SetUClientConnector(UClientConnector * udpClientConnector);

		bool HandleOutput(UdpBuffer & udpBuffer);
	protected:
		UClientConnector * udpClientConnector_;
	};
}
