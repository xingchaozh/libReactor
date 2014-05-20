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

LockFreeQueues::LockFreeQueues(void)
{
	InitQueue();
}

LockFreeQueues::~LockFreeQueues(void)
{
}

void LockFreeQueues::InitQueue()
{
	memset(m_ringBuffer,0,sizeof(RingArray));
	m_headOffset = 0;
	m_tailOffset = 1;
	m_ringBuffer[m_headOffset].type = RAN_TYPE_HEAD;
	m_ringBuffer[m_tailOffset].type = RAN_TYPE_TAIL;
}

int LockFreeQueues::EnQueue(RingArrayNodeDataType * value)
{
	RingArrayNodeType nodeType = RAN_TYPE_TAIL;
	int p = -1;
	int q = -1;
	do
	{
		p = m_tailOffset % MAX_SIZE_OF_RING_BUFFER;
		q = (m_tailOffset+1)% MAX_SIZE_OF_RING_BUFFER;

		if(m_ringBuffer[q].type != RAN_TYPE_EMPTY)
		{
			return ERR_FULL_QUEUE;
		}
	}
	while (CAS(&(m_ringBuffer[p].type),&nodeType,RAN_TYPE_CHANGE) != true);

	memcpy(&m_ringBuffer[p].value,value,sizeof(RingArrayNodeDataType));

	nodeType = RAN_TYPE_EMPTY;
	do
	{
		q = (m_tailOffset+1)% MAX_SIZE_OF_RING_BUFFER;
	}
	while(CAS(&(m_ringBuffer[q].type),&nodeType,RAN_TYPE_TAIL)!=true);

	nodeType = RAN_TYPE_CHANGE;
	do
	{
		p = m_tailOffset % MAX_SIZE_OF_RING_BUFFER;;
	}
	while(CAS(&(m_ringBuffer[p].type),&nodeType,RAN_TYPE_DATA)!=true);

	FetchADD(&m_tailOffset,1);

	return 0;
}

int LockFreeQueues::DeQueue(RingArrayNodeDataType * value)
{
	RingArrayNodeType nodeType = RAN_TYPE_HEAD;
	int p = -1;
	int q = -1;
	do
	{
		p = m_headOffset % MAX_SIZE_OF_RING_BUFFER;
		q = (m_headOffset+1)% MAX_SIZE_OF_RING_BUFFER;
		if (m_ringBuffer[q].type != RAN_TYPE_DATA)
		{
			return ERR_EMPTY_QUEUE;
		}
	}
	while(CAS(&(m_ringBuffer[p].type),&nodeType,RAN_TYPE_CHANGE) != true);

	memcpy(value,&m_ringBuffer[q].value,sizeof(RingArrayNodeDataType));
	
	nodeType = RAN_TYPE_DATA;
	do
	{
		q = (m_headOffset+1)% MAX_SIZE_OF_RING_BUFFER;
	}
	while(CAS(&(m_ringBuffer[q].type),&nodeType,RAN_TYPE_HEAD)!=true);

	nodeType = RAN_TYPE_CHANGE;
	do
	{
		p = m_headOffset % MAX_SIZE_OF_RING_BUFFER;
	} 
	while (CAS(&(m_ringBuffer[p].type),&nodeType,RAN_TYPE_EMPTY)!=true);

	FetchADD(&m_headOffset,1);

	return 0;
}