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
	m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL); 
}

void EventXO::SetEventX()
{
	SetEvent(m_hEvent);
}

void EventXO::WaitEvent()
{
	WaitForSingleObject(m_hEvent,INFINITE);
}

void EventXO::Destroy()
{
	CloseHandle(m_hEvent);
}
