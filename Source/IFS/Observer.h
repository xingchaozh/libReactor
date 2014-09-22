/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : ObserverX.h
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

#include "Subject.h"
class Observer
{
public:
	Observer(void);
	Observer(Subject * sub);
	virtual ~Observer(void);
public:
	virtual void Update(Subject * sub) = 0;
};
