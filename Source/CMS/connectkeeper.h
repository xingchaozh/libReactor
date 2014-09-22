/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : ConnectKeeper.h
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#ifndef HSICONNECTKEEPER_H
#define HSICONNECTKEEPER_H

#include "../Common/Common.h"
#include "../IFS/Observer.h"

class ConnectKeeper:
	public Observer
{
public:
	ConnectKeeper(UINT32 commLostTime_ = HSI_COMM_LOST_TIME);
    virtual ~ConnectKeeper();

public:
    void Execute();

    void SetCommEstablished(bool commEstablished);
    bool GetCommEstablished();

	void LeaveFreshCountReset();
	virtual void Update(Subject * sub);
protected:
	UINT32 leaveFreshCount_;
	UINT32 commLostTime_;
    bool commEstablished_;
};

typedef ConnectKeeper HSIConnectKeeper;
typedef ConnectKeeper HSRConnectKeeper;

#endif // HSICONNECTKEEPER_H

