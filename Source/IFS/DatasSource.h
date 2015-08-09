#pragma once

#include "../Common/DllCommon.h"

namespace libReactor
{
	class LIB_REACTOR_API DataSource
	{
	public:
		DataSource(){}
	public:
		virtual bool RetrieveData(void * data) = 0;
	};
}
