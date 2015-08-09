#include "ClientConnector.h"

namespace libReactor
{
	ClientConnector::ClientConnector(SokectType sokectType, long timeOut) :enabled_(true), socketType_(sokectType), timeOut_(timeOut)
	{
	}

	ClientConnector::~ClientConnector(void)
	{

	}

	void ClientConnector::SetEnable(bool bEnabled)
	{
		enabled_ = bEnabled;
	}

	void ClientConnector::ThreadEntryPoint()
	{
		while (enabled_)
		{
			ProcessOutput();
			ProcessInput();
		}
	}

	void ClientConnector::ProcessInput()
	{
		int iErrorCode = 0;
		if (socket_->IsReadable(timeOut_))
		{
			HandleInput();
		}
	}

	int ClientConnector::Initialize(string localClientHost,
		int localClientPort)
	{
		switch (socketType_)
		{
		case SOCKET_TYPE_TCP:
			socket_ = new TcpSocket();
			break;
		case SOCKET_TYPE_UDP:
			socket_ = new UdpSocket();
			break;
		default:
			break;
		}

		int ret = socket_->Bind(localClientHost, localClientPort);
		return ret;
	}

	void ClientConnector::SetTimeOut(long timeOut)
	{
		timeOut_ = timeOut;
	}
}
