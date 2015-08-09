#include "Thread.h"

namespace libReactor
{
	Thread::Thread(void):m_thread(NULL)
	{
	}

	Thread::~Thread(void)
	{
		if (!m_thread)
		{
			delete m_thread;
		}
	}

	void Thread::Start()
	{
		if (!m_thread)
		{
			m_thread = new std::thread(std::bind(&Thread::ThreadEntryPoint,this));
		}
	}

	void Thread::Join()
	{
		if (m_thread)
		{
			m_thread->join();
		}
	}

	unsigned int Thread::GetThreadId()
	{
		if (m_thread)
		{
			return m_thread->get_id().hash();
		}
		return 0;
	}

	std::thread* Thread::RunAsThread(std::function<void ()> fun)
	{
		return new std::thread(fun);
	}
}
