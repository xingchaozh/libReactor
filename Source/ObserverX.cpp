/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : ObserverX.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "ObserverX.h"

ObserverX::ObserverX(void)
{
}

ObserverX::ObserverX(SubjectX * sub)
{
	sub->Attach(this);
}

ObserverX::~ObserverX(void)
{
}
