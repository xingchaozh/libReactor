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

class Observer;
class Subject
{
public:
	Subject(void);
	virtual ~Subject(void);
public:
	virtual void Attach(Observer * obv);
	virtual void Detach(Observer * obv);
	virtual void Notify();
private:
	list<Observer *> * _obvs;
};
