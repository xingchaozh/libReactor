/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
*
* Filename      : EventXO.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "EventXO.h"

EventXO::EventXO(void)
{
	CreateEventX();
}

EventXO::~EventXO(void)
{
	Destroy();
}

void EventXO::CreateEventX()
{
	hEvent_ = CreateEvent(NULL, FALSE, FALSE, NULL); 
}

void EventXO::SetEventX()
{
	SetEvent(hEvent_);
}

void EventXO::WaitEvent()
{
	WaitForSingleObject(hEvent_,INFINITE);
}

void EventXO::Destroy()
{
	CloseHandle(hEvent_);
}
