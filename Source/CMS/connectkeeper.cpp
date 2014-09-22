/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : ConnectKeeper.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "connectkeeper.h"

ConnectKeeper::ConnectKeeper(UINT32 commLostTime):leaveFreshCount_(0),
	commLostTime_(commLostTime),
	commEstablished_(false)
{
}

ConnectKeeper::~HSIConnectKeeper()
{
}

void ConnectKeeper::Execute()
{
}

void ConnectKeeper::SetCommEstablished(bool commEstablished)
{
    commEstablished_ = commEstablished;
    if(commEstablished_)
    {
        leaveFreshCount_ = 0;
    }
}

bool ConnectKeeper::GetCommEstablished()
{
    return commEstablished_;
}

void ConnectKeeper::LeaveFreshCountReset()
{
	if(!GetCommEstablished())
	{
		SetCommEstablished(true);
		printf("ConnectKeeper::SetCommEstablished(true)\n");
	}
	leaveFreshCount_ = 0;
}

void ConnectKeeper::Update(Subject * sub)
{
	if(GetCommEstablished())
	{
		leaveFreshCount_ += 1;
		if (leaveFreshCount_ > commLostTime_ / APP_CYCLE_TIME)
		{
			SetCommEstablished(false);
			printf("ConnectKeeper::Update: Communication Lost!\n");
		}
	}
}
