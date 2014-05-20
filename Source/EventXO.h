/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
*
* Filename      : EventXO.h
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

class EventXO
{
public:
	EventXO(void);
	~EventXO(void);
public:
	void CreateEventX();
	void SetEventX();
	void WaitEvent();
	void Destroy();
private:
	HANDLE m_hEvent;
};

