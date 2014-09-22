/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : CMessageTimer.h
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

#include <functional>
#include <vector>

#include <windows.h>

#include "MessageTimerDefine.h"

class CMessageTimer
{
public:
	CMessageTimer() : m_Timer(MAX_COUNT_TIMER)
	{
	}

	BOOL SetTimer(HWND hWnd, UINT uEvent, DWORD dwPeriod)
	{
		if(!IsWindow(hWnd) || !TIMER_EVENT_IN_RANGE(uEvent))
			return FALSE;

		TIMER_STRUCT &Struct = m_Timer[uEvent];
		_ASSERT(Struct.hTimer == NULL && Struct.Handler == NULL);

		WAITORTIMERCALLBACK TimerCallback = NULL;
		DISPATCH_TIMER_CALLBACK(uEvent, TimerCallback)

		BOOL bRet = CreateTimerQueueTimer(&Struct.hTimer, NULL, TimerCallback, this, 0, dwPeriod, 0);
		if(bRet)
		{
			Struct.Handler = new CMessageTimerHandler(uEvent, hWnd);
		}
		return bRet;
	}

	template <typename T>
	BOOL SetTimer(UINT uEvent, DWORD dwPeriod, T Function)
	{
		if(!TIMER_EVENT_IN_RANGE(uEvent))
			return FALSE;

		TIMER_STRUCT &Struct = m_Timer[uEvent];
		_ASSERT(Struct.hTimer == NULL && Struct.Handler == NULL);

		WAITORTIMERCALLBACK TimerCallback = NULL;
		DISPATCH_TIMER_CALLBACK(uEvent, TimerCallback)

		BOOL bRet = CreateTimerQueueTimer(&Struct.hTimer, NULL, TimerCallback, this, 0, dwPeriod, 0);
		if(bRet)
		{
			Struct.Handler = new CBindTimerHandler(uEvent, std::tr1::bind(Function, std::tr1::placeholders::_1));
		}
		return bRet;
	}

	template <typename T, typename CLASS>
	BOOL SetTimer(UINT uEvent, DWORD dwPeriod, T Function, CLASS *lpClass)
	{
		if(!TIMER_EVENT_IN_RANGE(uEvent) || lpClass == NULL)
			return FALSE;

		TIMER_STRUCT &Struct = m_Timer[uEvent];
		_ASSERT(Struct.hTimer == NULL && Struct.Handler == NULL);

		WAITORTIMERCALLBACK TimerCallback = NULL;
		DISPATCH_TIMER_CALLBACK(uEvent, TimerCallback)

		BOOL bRet = CreateTimerQueueTimer(&Struct.hTimer, NULL, TimerCallback, this, 0, dwPeriod, 0);
		if(bRet)
		{
			Struct.Handler = new CBindTimerHandler(uEvent, std::tr1::bind(Function, lpClass, std::tr1::placeholders::_1));
		}
		return bRet;
	}

	BOOL KillTimer(UINT uEvent)
	{
		if(!TIMER_EVENT_IN_RANGE(uEvent))
			return FALSE;

		BOOL bRet = FALSE;
		TIMER_STRUCT &Struct = m_Timer[uEvent];

		if(Struct.hTimer != NULL)
		{
			bRet = DeleteTimerQueueTimer(NULL, Struct.hTimer, INVALID_HANDLE_VALUE);
			if(!bRet)
			{
				bRet = GetLastError() == ERROR_IO_PENDING;
			}

			Struct.hTimer = NULL;
		}

		if(Struct.Handler != NULL)
		{
			delete Struct.Handler;
			Struct.Handler = NULL;
		}

		return bRet;
	}

private:
	struct TIMER_STRUCT
	{
		TIMER_STRUCT() : hTimer(NULL), Handler(NULL) {}
		~TIMER_STRUCT() {_ASSERT(hTimer == NULL && Handler == NULL);}

		HANDLE hTimer;
		CTimerHandler *Handler;
	};

private:
	DEFINE_TIMER_CALLBACK(0)
	DEFINE_TIMER_CALLBACK(1)
	DEFINE_TIMER_CALLBACK(2)
	DEFINE_TIMER_CALLBACK(3)

private:
	std::vector<TIMER_STRUCT> m_Timer;
};
