#include "ConnectKeeper.h"
#include "../IFS/IFS.h"

namespace libReactor
{
	ConnectKeeper::ConnectKeeper(UINT32 commLostTime) :m_leaveFreshCount(0),
		m_commLostTime(commLostTime),
		m_commEstablished(false),
		m_description("")
	{
	}

	ConnectKeeper::~ConnectKeeper()
	{
	}

	void ConnectKeeper::Execute()
	{
	}

	void ConnectKeeper::SetCommEstablished(bool commEstablished)
	{
		m_commEstablished = commEstablished;
		if (m_commEstablished)
		{
			m_leaveFreshCount = 0;
		}
	}

	bool ConnectKeeper::GetCommEstablished()
	{
		return m_commEstablished;
	}

	void ConnectKeeper::LeaveFreshCountReset()
	{
		if (!GetCommEstablished())
		{
			SetCommEstablished(true);
			IFS::PrintErrors("ConnectKeeper::SetCommEstablished(true) : %s !\n", m_description.c_str());
		}
		m_leaveFreshCount = 0;
	}

	void ConnectKeeper::Update(Subject * sub)
	{
		if (GetCommEstablished())
		{
			m_leaveFreshCount += 1;
			if (m_leaveFreshCount > m_commLostTime / APP_CYCLE_TIME)
			{
				SetCommEstablished(false);
				IFS::PrintErrors("ConnectKeeper::Update: Communication Lost: %s !\n", m_description.c_str());
			}
		}
	}

	void ConnectKeeper::SetDescription(std::string description)
	{
		this->m_description = description;
	}
}
