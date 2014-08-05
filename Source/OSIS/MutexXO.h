/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : MutexXO.h
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
#include <windows.h>          // for HANDLE

class MutexXO
{
public:
	MutexXO(void);
	~MutexXO(void);
public:
	void MutexInit();
	DWORD MutexLock(DWORD dwMilliseconds);
	DWORD MutexLock();
	BOOL MutexUnlock();
private:
	HANDLE hMutex_;
};

