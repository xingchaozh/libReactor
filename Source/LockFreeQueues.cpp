/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : LockFreeQueues.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "LockFreeQueues.h"

#include <math.h>

LockFreeQueue::LockFreeQueue(int s)
{
	size_ = s;//s shall be exponential times of 2, such as 16, 32, 64, 128, 256, 521, 1024 and so on. or fast modulo operation will fail.
	exponent_size_ = (int)(log(size_)/log(2));
	head_index_ = 0;
	tail_index_ = 0;
	element_num_ = 0;

	InitQueue();
}

//Non-ThreadSafe
bool LockFreeQueue::InitQueue(void)
{
	flags_array_ = new(std::nothrow) std::atomic<int>[size_];
	if (flags_array_ == NULL)
		return false;
	memset(flags_array_, 0, size_);

	ring_array_ = reinterpret_cast<ElementT*>(new(std::nothrow) char[size_ * sizeof(ElementT)]);
	if (ring_array_ == NULL)
		return false;
	memset(ring_array_, 0, size_ * sizeof(ElementT));

	return true;
}

//ThreadSafe
bool LockFreeQueue::EnQueue(const ElementT & ele)
{
	if (!(element_num_ < size_))
		return false;

	int cur_tail_index = tail_index_;
	std::atomic<int> * cur_tail_flag_index = flags_array_ + cur_tail_index;

	while (!CAS(cur_tail_flag_index, 0, 1)) 
	{
		cur_tail_index = tail_index_;
		cur_tail_flag_index = flags_array_ + cur_tail_index;
	}

	//int update_tail_index = (cur_tail_index + 1) % size_;
	int update_tail_index = (cur_tail_index + 1) & ((1<<exponent_size_) - 1);

	CAS(&tail_index_, cur_tail_index, update_tail_index);
	*(ring_array_ + cur_tail_index) = ele;

	FetchADD(cur_tail_flag_index, 1);
	FetchADD(&element_num_, 1);

	return true;
}

//ThreadSafe
bool LockFreeQueue::DeQueue(ElementT * ele) 
{
	if (!(element_num_ > 0))
		return false;

	int cur_head_index = head_index_;
	std::atomic<int> * cur_head_flag_index = flags_array_ + cur_head_index;
	while (!CAS(cur_head_flag_index, 2, 3)) 
	{
		cur_head_index = head_index_;
		cur_head_flag_index = flags_array_ + cur_head_index;

		if (!(element_num_ > 0))
			return false;
	}

	//int update_head_index = (cur_head_index + 1) % size_;
	int update_head_index = (cur_head_index + 1) & ((1<<exponent_size_) - 1);

	CAS(&head_index_, cur_head_index, update_head_index);

	*ele = *(ring_array_ + cur_head_index);

	FetchSub(cur_head_flag_index, 3);
	FetchSub(&element_num_, 1);

	return true;
}
