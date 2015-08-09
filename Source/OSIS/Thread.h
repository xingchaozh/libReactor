#pragma once

#include "../Common/DllCommon.h"
#include <thread>

namespace libReactor
{
	class LIB_REACTOR_API Thread
	{
	public:
		Thread(void);
		virtual ~Thread(void);
	public:
		void Start();
		void Join();
		unsigned int GetThreadId();

		virtual void ThreadEntryPoint() {};

		static std::thread* RunAsThread(std::function<void ()> fun);
	private:
		std::thread * m_thread;
	};
}
