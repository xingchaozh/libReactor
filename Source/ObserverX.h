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

#include "SubjectX.h"
class ObserverX
{
public:
	ObserverX(void);
	ObserverX(SubjectX * sub);
	virtual ~ObserverX(void);
public:
	virtual void Update(SubjectX * sub) = 0;
};
