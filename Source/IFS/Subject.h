#pragma once

#include <list>
using namespace std;

#include "../Common/DllCommon.h"

namespace libReactor
{
	class Observer;
	class LIB_REACTOR_API Subject
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
}
