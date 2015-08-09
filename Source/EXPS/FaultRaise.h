#pragma once

#include "../Common/Common.h"
#include "../CMS/lockfreequeue.h"

#include <stdarg.h>

namespace libReactor
{
	class BufferLogger;
	class LIB_REACTOR_API FaultRaise
	{
	protected:
		FaultRaise();
		~FaultRaise();

	public:
		bool SetFault(const bool iFaultFlag, const ErrorCode iErrorCode, const string iErrorMessage);
		bool GetLastFault(FaultElement * faultElement);

		int PrintErrors(const char * _format, const va_list _args);
		int PrintErrors(const char * _format...);

		static FaultRaise * Instance();

		void Destroy();
	private:
		LockFreeQueue<FaultElement> * faultElementQueue_;
		static FaultRaise * instance;
		BufferLogger * logger_;
		bool fileOutputEnabled_;
	};
}
