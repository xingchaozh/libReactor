/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : LockFreeQueues.h
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#ifndef LOCKFREEQUEUE_H
#define LOCKFREEQUEUE_H

#include "CommonX.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include <atomic>

using namespace std;

typedef UdpBufferRev ElementT;

class LockFreeQueue
{
public:
	LockFreeQueue(int s = MAX_SIZE_OF_RING_BUFFER);
	~LockFreeQueue() {}

	bool InitQueue(void);

	bool EnQueue(const ElementT & ele);

	bool DeQueue(ElementT * ele);

	//__sync_bool_compare_and_swap
	template<class T>
	inline bool CAS (std::atomic<T> * reg, T old, T newVal)
	{
		return std::atomic_compare_exchange_weak(reg,&old,newVal);
	}

	//__sync_fetch_and_add
	inline int FetchADD(std::atomic<int> * v, int add)
	{
		return std::atomic_fetch_add(v,add) ;
	}

	//__sync_fetch_and_sub
	inline int FetchSub(std::atomic<int> * v, int add)
	{
		return std::atomic_fetch_sub(v,add) ;
	}

private:
	ElementT * ring_array_;
	std::atomic<int> * flags_array_;//flags: 0£ºempty£»1£ºenqueue-ing 2£ºenqueue-able;3,dequeue-ing;
	int size_;
	int exponent_size_;
	std::atomic<int> element_num_;
	std::atomic<int> head_index_;
	std::atomic<int> tail_index_;
};


#endif // LOCKFREEQUEUE_H
