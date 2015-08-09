#pragma once

#include "../IFS/IFSInternal.h"

namespace libReactor
{
	class SvcHandler :
		public libReactor::Thread
	{
	public:
		SvcHandler(void);
		virtual ~SvcHandler(void);
	protected:
		virtual void ThreadEntryPoint() = 0;
	};
}
