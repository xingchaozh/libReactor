#pragma once

#include "../Common/DllCommon.h"

namespace libReactor
{
#define MAX_COUNT_TIMER 4

#define TIMER_EVENT_IN_RANGE(e) (((e) >= 0) && ((e) < MAX_COUNT_TIMER))

#define DISPATCH_TIMER_CALLBACK(e, cb) \
	switch(e) \
	{ \
	case 0: \
		cb = TimerCallback0; \
		break; \
	case 1: \
		cb = TimerCallback1; \
		break; \
	case 2: \
		cb = TimerCallback2; \
		break; \
	case 3: \
		cb = TimerCallback3; \
		break; \
	default: \
		_ASSERT(FALSE); \
	}

#define DEFINE_TIMER_CALLBACK(e) \
	static VOID CALLBACK TimerCallback##e(LPVOID lpParameter, BOOLEAN TimerFired) \
	{ \
		CMessageTimer *pThis = (CMessageTimer*)lpParameter; \
		(pThis->m_Timer[e].Handler)->Handle(); \
	}

	class LIB_REACTOR_API CTimerHandler
	{
	public:
		CTimerHandler(UINT uEvent) : m_uEvent(uEvent)
		{
			_ASSERT(TIMER_EVENT_IN_RANGE(m_uEvent));
		}

		virtual ~CTimerHandler()
		{
		}

		virtual VOID Handle() CONST PURE;

	protected:
		UINT m_uEvent;
	};

	class LIB_REACTOR_API CMessageTimerHandler : public CTimerHandler
	{
	public:
		CMessageTimerHandler(UINT uEvent, HWND TimerWnd) : CTimerHandler(uEvent), m_hWnd(TimerWnd)
		{
		}

		virtual VOID Handle() CONST
		{
			PostMessage(m_hWnd, WM_TIMER, m_uEvent, 0);
		}

	private:
		HWND m_hWnd;
	};

	class LIB_REACTOR_API CBindTimerHandler : public CTimerHandler
	{
	public:
		CBindTimerHandler(UINT uEvent, const std::tr1::function<VOID(UINT)> &TimerFunc) : CTimerHandler(uEvent), m_Functional(TimerFunc)
		{
		}

		virtual VOID Handle() CONST
		{
			m_Functional(m_uEvent);
		}

	private:
		std::tr1::function<VOID(UINT)> m_Functional;
	};
}
