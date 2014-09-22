/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : UBufferContainer.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "UBufferContainer.h"


UBufferContainer::UBufferContainer(UINT16 buffer_size)
{
}


UBufferContainer::~UBufferContainer(void)
{
}

bool UBufferContainer::EnQueue(const UdpBuffer & udpBuffer)
{
	bool result = BufferContainer::EnQueue(udpBuffer);
	this->Notify();
	return result;
}


