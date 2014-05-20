/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : SubjectX.h
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

#include <list>
using namespace std;

class ObserverX;
class SubjectX
{
public:
	SubjectX(void);
	virtual ~SubjectX(void);
public:
	virtual void Attach(ObserverX * obv);
	virtual void Detach(ObserverX * obv);
	virtual void Notify();
private:
	list<ObserverX *> * _obvs;
};
