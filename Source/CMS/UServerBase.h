#pragma once

#include "../Common/Common.h"

#include <vector>
using namespace std;

namespace libReactor
{
	class UDataReader;
	class UDataProcesser;
	class UServerDataHandler;
	class UBufferContainer;
	class UServerAccepter;

	class UServerBase
	{
	public:
		UServerBase(UINT16 bufferSize = USERVER_BUFFER_SIZE,
			UINT16 numDataReader = NUM_USERVER_DATA_READER,
			UINT16 unmDataProcesser = NUM_USERVER_DATA_PROCESSER,
			long timeOut = USERVER_LISTEN_TIMEOUT);
		virtual ~UServerBase(void);

	public:
		bool SetParameters(UINT16 bufferSize = USERVER_BUFFER_SIZE,
			UINT16 numDataReader = NUM_USERVER_DATA_READER,
			UINT16 numDataProcesser = NUM_USERVER_DATA_PROCESSER,
			long timeOut = USERVER_LISTEN_TIMEOUT);
		void Execute(string localServerHost, int localServerPort, string dataHandlerClassName);
		void Destroy();

		bool HandleOutput(UdpBuffer & udpBuffer);

	protected:
		UServerAccepter * serverAccepter_;
		vector<UDataReader *> vecUDataReader_;
		vector<UDataProcesser *> vecDataProcesser_;
		vector<UServerDataHandler *> vecDataHandler_;
		UBufferContainer * UBufferContainer_;
		bool ServiceStarted_;

	protected:
		UINT16 bufferSize_;
		UINT16 numDataReader_;
		UINT16 numDataProcesser_;
		long timeOut_;
	};
}
