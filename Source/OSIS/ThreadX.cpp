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

ThreadX::ThreadX():handle_(NULL),threadId_(0),threadName_("")
{
}

ThreadX::~ThreadX()  
{
	if(handle_ != NULL)
	{
		CloseHandle(handle_);
	}
}

void ThreadX::Start(bool bSuspend)
{
	printf("One thread is created!\n");
	handle_ = ThreadX::BeginThreadXDefault(this,&threadId_, bSuspend);
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
	return ResumeThread(handle_);
}

unsigned long ThreadX::SuspendThreadX()
{
	return SuspendThread(handle_);
}

int ThreadX::TerminateThreadX(unsigned long dwExitCode)
{
	return TerminateThread(handle_,dwExitCode);
}

int ThreadX::SetThreadPriorityX(int nPriority)
{
	return SetThreadPriority(handle_,nPriority);
}

int ThreadX::GetThreadPriorityX()
{
	return GetThreadPriority(handle_);
}

void ThreadX::ExitThreadX(unsigned long dwExitCode)
{
	ExitThread(dwExitCode);
}

unsigned long ThreadX::WaitForExit(unsigned long dwMilliseconds)
{
	return WaitForSingleObject(handle_,dwMilliseconds);
}

string ThreadX::GetThreadName()
{
	return threadName_;
}

void ThreadX::SetThreadName(string threadName)
{
	threadName_ = threadName;
}

unsigned int ThreadX::GetThreadId()
{
	return threadId_;
}

HANDLE ThreadX::GetThreadHandle()
{
	return handle_;
}
