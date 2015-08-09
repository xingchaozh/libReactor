#pragma once

#include <condition_variable>

namespace libReactor
{
	class Event
	{
	public:
		Event(void);
		~Event(void);
	public:
		void Set();
		void Wait();
	private:
		/*mutable */std::mutex mutex_;
		std::condition_variable condvar_;
		bool m_ready;
	};
}
