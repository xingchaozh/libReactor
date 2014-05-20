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
	CloseHandle(m_hMutex);
}

void MutexXO::MutexInit()
{
	m_hMutex = CreateMutex(NULL,FALSE,NULL);
}

DWORD MutexXO::MutexLock(DWORD dwMilliseconds)
{
	return WaitForSingleObject(m_hMutex,dwMilliseconds);
}

DWORD MutexXO::MutexLock()
{
	return WaitForSingleObject(m_hMutex,INFINITE);
}

BOOL MutexXO::MutexUnlock()
{
	return ReleaseMutex(m_hMutex);
}