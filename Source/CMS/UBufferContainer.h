/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : UBufferContainer.h
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
#include "../cms/buffercontainer.h"
#include "../IFS/Subject.h"

class UBufferContainer :
	public BufferContainer,public Subject
{
public:
	UBufferContainer(UINT16 buffer_size = MAX_SIZE_OF_RING_BUFFER);
	virtual ~UBufferContainer(void);
public:
	virtual bool EnQueue(const UdpBuffer & udpBuffer);
};

