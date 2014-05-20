/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : UdpDataProcesser.h
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
#include "observerx.h"
#include "UdpServerAccepter.h"
#include "threadx.h"

#include "EventXO.h"

class UdpDataProcesser :
	public ObserverX, public ThreadX
{
public:
	UdpDataProcesser(void);
	UdpDataProcesser(UdpServerAccepter * myServerAccepter);
	~UdpDataProcesser(void);
	void SetEnable(bool bEnabled)
	{
		m_bEnabled = bEnabled;
	}
protected:

	void ProcessData(UdpBufferRev * bufferRev);
	virtual void ThreadEntryPoint();
	virtual void Update(SubjectX * sub);

private:
	UdpServerAccepter * m_udpServerAccepter;
	EventXO * m_hThreadEventNewData;
	bool m_bEnabled;
};

