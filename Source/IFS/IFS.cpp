/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : IFS.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "IFS.h"

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

unsigned int GetCurrentThreadId_X()
{
#ifdef WIN32
	return::GetCurrentThreadId();
#else
	returnthread_self();
#endif
}


