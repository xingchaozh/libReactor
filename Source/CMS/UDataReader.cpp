#include "UDataReader.h"
#include "UServerAccepter.h"
#include "BufferContainer.h"

namespace libReactor
{
UDataReader::UDataReader(UServerAccepter * udpServerAccepter)
{
	udpServerAccepter_ = udpServerAccepter;
	udpServerAccepter_->Attach(this);

	event_ = new libReactor::Event();
	enabled_ = true;

	bufferListRev_ = NULL;
}


UDataReader::~UDataReader(void)
{
	delete event_;
}

void UDataReader::Update(Subject * sub)
{
	event_->Set();
}

void UDataReader::ThreadEntryPoint()
{
	while (enabled_)
	{
		event_->Wait();
		if (!enabled_)
		{
			break;
		}
		Read();
	}
}

int UDataReader::Read()
{
	char * ptr = (char *)&(bufferRev_.buffer.message);

	bufferRev_.buffer.length = udpServerAccepter_->RetrieveData(bufferRev_);

	if(SOCKET_ERROR == bufferRev_.buffer.length)
	{
		return SOCKET_ERROR;
	}
	else if(0 == bufferRev_.buffer.length)
	{
		return 0;
	}
	else
	{
		//EnQueue the income data
		if(NULL != bufferListRev_)
		{
			bufferListRev_->EnQueue(bufferRev_);
		}
	}

	return bufferRev_.buffer.length;
}

void UDataReader::SetBufferListRev(BufferContainer * bufferListRev)
{
	bufferListRev_ = bufferListRev;
}

void UDataReader::SetEnable(bool bEnabled)
{
	enabled_ = bEnabled;
}
}