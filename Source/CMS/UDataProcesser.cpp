#include "UDataProcesser.h"
#include "UBufferContainer.h"

namespace libReactor
{
	UDataProcesser::UDataProcesser(UBufferContainer * bufferContainer) :enabled_(true), dataHandler_(NULL)
	{
		bufferContainer_ = bufferContainer;
		bufferContainer_->Attach(this);

		threadEventNewData_ = new libReactor::Event();
	}

	UDataProcesser::~UDataProcesser(void)
	{
		delete threadEventNewData_;
	}

	void UDataProcesser::Update(Subject * sub)
	{
		threadEventNewData_->Set();
	}

	void UDataProcesser::ProcessData(UdpBuffer & bufferRev)
	{
		if (dataHandler_ != NULL)
		{
			dataHandler_->DataHanle(bufferRev);
		}
	}

	void UDataProcesser::ThreadEntryPoint()
	{
		while (enabled_)
		{
			threadEventNewData_->Wait();
			if (!enabled_)
			{
				break;
			}

			UdpBuffer bufferRev;
			while (bufferContainer_->DeQueue(&bufferRev))
			{
				ProcessData(bufferRev);
			}
		}
	}

	void UDataProcesser::SetEnable(bool bEnabled)
	{
		enabled_ = bEnabled;
	}
}
