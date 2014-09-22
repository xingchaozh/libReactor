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
#include "Subject.h"
#include "Observer.h"

Subject::Subject(void)
{
	_obvs = new list<Observer *>;
}


Subject::~Subject(void)
{
}

void Subject::Attach(Observer * obv)
{
	_obvs->push_back(obv);
}

void Subject::Detach(Observer * obv)
{
	_obvs->remove(obv);
}

void Subject::Notify()
{
	for (list<Observer*>::iterator it = _obvs->begin(); it != _obvs->end(); it++)
	{
		(*it)->Update(this);
	}
}
