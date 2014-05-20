/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : SubjectX.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "SubjectX.h"
#include "ObserverX.h"

SubjectX::SubjectX(void)
{
	_obvs = new list<ObserverX *>;
}


SubjectX::~SubjectX(void)
{
}

void SubjectX::Attach(ObserverX * obv)
{
	_obvs->push_front(obv);
}

void SubjectX::Detach(ObserverX * obv)
{
	_obvs->remove(obv);
}

void SubjectX::Notify()
{
	for (list<ObserverX*>::iterator it = _obvs->begin(); it != _obvs->end(); it++)
	{
		(*it)->Update(this);
	}
}
