/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : BufferContainer.h
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#ifndef BUFFERCONTAINER_H
#define BUFFERCONTAINER_H

#include "LockFreeQueue.h"

class BufferContainer
{
public:
	BufferContainer(UINT16 buffer_size = MAX_SIZE_OF_RING_BUFFER);
	~BufferContainer();

	virtual bool EnQueue(const UdpBuffer & udpBuffer);

	bool DeQueue(UdpBuffer * udpBuffer);

	bool IsEmpty();
private:
	LockFreeQueue<UdpBuffer> * queue_;
};

#endif // BUFFERCONTAINER_H
