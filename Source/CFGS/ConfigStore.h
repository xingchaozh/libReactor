#pragma once

#include <string>
using namespace std;

#include "../Common/Common.h"

namespace libReactor
{
	class LIB_REACTOR_API ConfigStore
	{
	public:
		ConfigStore(void){}
		virtual ~ConfigStore(void){}
	public:
		static string m_appName;
		static UINT16 m_devId;
	};
}
