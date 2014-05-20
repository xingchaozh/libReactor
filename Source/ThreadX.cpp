/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : ThreadX.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "ThreadX.h"

ThreadX::ThreadX():m_handle(NULL),m_threadId(0),m_threadName("")
{
}

ThreadX::~ThreadX()  
{
	if(m_handle != NULL)
	{
		CloseHandle(m_handle);
	}
}

void ThreadX::Start(bool bSuspend)
{
	m_handle = ThreadX::BeginThreadXDefault(this,&m_threadId, bSuspend);
}

HANDLE ThreadX::BeginThreadXDefault(void * _ArgList, unsigned int * threadId, bool bSuspend)
{
	unsigned _InitFlag = 0;
	if (bSuspend)
	{
		_InitFlag = CREATE_SUSPENDED;
	}
	return BeginThreadX(NULL, 
		0,
		_ArgList, 
		_InitFlag, 
		threadId);
}

HANDLE ThreadX::BeginThreadX(void * _Security, 
							 unsigned _StackSize,
							 void * _ArgList, 
							 unsigned _InitFlag, 
							 unsigned * _ThrdAddr)
{
	HANDLE    hth;  

	hth = (HANDLE)_beginthreadex( _Security,  // security  
		_StackSize,                           // stack size  
		ThreadX::ThreadStaticEntryPoint,      // start address
		_ArgList,                             // arg list  
		_InitFlag,                            // init flag
		_ThrdAddr);                           // thread id

	if ( hth == 0 )
	{
		printf("Failed to create thread\n");
	}
	return hth;
}

unsigned __stdcall ThreadX::ThreadStaticEntryPoint(void * pThis)  
{
	ThreadX * pthX = (ThreadX*)pThis;   // the tricky cast
	pthX->ThreadEntryPoint();           // now call the true entry-point-function
	return 1;                           // the thread exit code
}

unsigned long ThreadX::ResumeThreadX()
{
	return ResumeThread(m_handle);
}

unsigned long ThreadX::SuspendThreadX()
{
	return SuspendThread(m_handle);
}

int ThreadX::TerminateThreadX(unsigned long dwExitCode)
{
	return TerminateThread(m_handle,dwExitCode);
}

int ThreadX::SetThreadPriorityX(int nPriority)
{
	return SetThreadPriority(m_handle,nPriority);
}

int ThreadX::GetThreadPriorityX()
{
	return GetThreadPriority(m_handle);
}

void ThreadX::ExitThreadX(unsigned long dwExitCode)
{
	ExitThread(dwExitCode);
}

unsigned long ThreadX::WaitForExit(unsigned long dwMilliseconds)
{
	return WaitForSingleObject(m_handle,dwMilliseconds);
}

string ThreadX::GetThreadName()
{
	return m_threadName;
}

void ThreadX::SetThreadName(string threadName)
{
	m_threadName = threadName;
}

unsigned int ThreadX::GetThreadId()
{
	return m_threadId;
}

HANDLE ThreadX::GetThreadHandle()
{
	return m_handle;
}
