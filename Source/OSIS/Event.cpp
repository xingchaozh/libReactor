#include "Event.h"

namespace libReactor
{
	Event::Event(void):m_ready(false)
	{
	}

	Event::~Event(void)
	{
	}

	void Event::Set()
	{
		{
			std::lock_guard<std::mutex> lock(mutex_);
			m_ready = true;
		}
		condvar_.notify_one();
	}

	void Event::Wait()
	{
		std::unique_lock<std::mutex> lock(mutex_);
		condvar_.wait(lock, [this]{return m_ready; });
		{
			m_ready = false;
		}
	}
}
