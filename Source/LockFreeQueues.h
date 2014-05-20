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
#pragma once

#include "CommonX.h"

#include <iostream>       // std::cout
#include <atomic>         // std::atomic
#include <thread>         // std::thread

typedef UdpBufferRev RingArrayNodeDataType;

#define MAX_SIZE_OF_RING_BUFFER 64
typedef enum _RingArrayNodeType
{
	RAN_TYPE_EMPTY,      //0
	RAN_TYPE_HEAD,       //1
	RAN_TYPE_TAIL,       //2
	RAN_TYPE_DATA,       //3
	RAN_TYPE_CHANGE      //4
}RingArrayNodeType;
typedef struct _RingBArrayNode
{
	std::atomic<RingArrayNodeType> type;
	RingArrayNodeDataType value;
}RingArrayNode;
typedef RingArrayNode RingArray[MAX_SIZE_OF_RING_BUFFER];

#define ERR_EMPTY_QUEUE -1
#define ERR_FULL_QUEUE -2

class LockFreeQueues
{
public:
	LockFreeQueues(void);
	virtual ~LockFreeQueues(void);
public:
	int EnQueue(RingArrayNodeDataType * value);
	int DeQueue(RingArrayNodeDataType * value);
protected:
	void InitQueue();

	//compare_and_swap
	template<class T>
	bool CAS (std::atomic<T> * reg, T * old, T newVal)
	{//atomic_compare_exchange_weak
		return std::atomic_compare_exchange_weak(reg,old,newVal);
	}

	//__sync_fetch_and_add
	int FetchADD(std::atomic<int> * v, int add)
	{//atomic_fetch_add
		return std::atomic_fetch_add(v,add) ;
	}
protected:
	RingArray m_ringBuffer;
	std::atomic<int> m_headOffset;
	std::atomic<int> m_tailOffset;
};

