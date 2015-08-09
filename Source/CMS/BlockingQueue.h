#pragma once

#include <condition_variable>
#include <list>
#include <assert.h>

namespace libReactor
{
	template<typename T>
	class BlockingQueue
	{
	public:
		BlockingQueue()/* : mutex_(), condvar_(), queue_()*/
		{
		}

		virtual ~BlockingQueue(void)
		{
		}

		void Put(const T& task)
		{
			{
				std::lock_guard<std::mutex> lock(mutex_);
				queue_.push_back(task);
			}
			condvar_.notify_all();
		}

		void Take(T * front)
		{
			std::unique_lock<std::mutex> lock(mutex_);
			condvar_.wait(lock, [this]{return !queue_.empty(); });
			assert(!queue_.empty());
			*front = (queue_.front());
			queue_.pop_front();
		}

		size_t Size() const
		{
			std::lock_guard<std::mutex> lock(mutex_);
			return queue_.size();
		}

	private:
		BlockingQueue(const BlockingQueue& rhs);
		BlockingQueue & operator = (const BlockingQueue& rhs);

	private:
		/*mutable */std::mutex mutex_;
		std::condition_variable condvar_;
		std::list<T> queue_;
	};
};
