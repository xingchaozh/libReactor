/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : MutexXO.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "MutexXO.h"

MutexXO::MutexXO(void)
{
	MutexInit();
}

MutexXO::~MutexXO(void)
{
	CloseHandle(hMutex_);
}

void MutexXO::MutexInit()
{
	hMutex_ = CreateMutex(NULL,FALSE,NULL);
}

DWORD MutexXO::MutexLock(DWORD dwMilliseconds)
{
	return WaitForSingleObject(hMutex_,dwMilliseconds);
}

DWORD MutexXO::MutexLock()
{
	return WaitForSingleObject(hMutex_,INFINITE);
}

BOOL MutexXO::MutexUnlock()
{
	return ReleaseMutex(hMutex_);
}