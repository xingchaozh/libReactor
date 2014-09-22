/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : SvcHandler.h
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

#include "../IFS/IFSInternal.h"

class SvcHandler :
	public ThreadX
{
public:
	SvcHandler(void);
	virtual ~SvcHandler(void);
protected:
	virtual void ThreadEntryPoint() = 0;
};
