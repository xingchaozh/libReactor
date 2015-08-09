#pragma once

#include "../Common/Common.h"
#include "../IFS/Observer.h"

namespace libReactor
{
	class LIB_REACTOR_API ConnectKeeper :
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

		void SetDescription(std::string description);
	protected:
		UINT32 m_leaveFreshCount;
		UINT32 m_commLostTime;
		bool m_commEstablished;
		std::string m_description;
	};

	typedef ConnectKeeper HSIConnectKeeper;
	typedef ConnectKeeper HSRConnectKeeper;
}


