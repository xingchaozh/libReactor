#pragma once

#include "Subject.h"

namespace libReactor
{
	class LIB_REACTOR_API Observer
	{
	public:
		Observer(void)
		{

		}
		Observer(Subject * sub)
		{
			sub->Attach(this);
		}
		virtual ~Observer(void)
		{

		}
	public:
		virtual void Update(Subject * sub) = 0;
	};
}
