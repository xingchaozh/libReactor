#include "UClient.h"
#include "UClientBase.h"

namespace libReactor
{
	UClient::UClient(void)
	{
		m_clientBase = new UClientBase();
	}

	UClient::~UClient(void)
	{
		delete m_clientBase;
	}

	void UClient::Execute(string localClientHost,
		int localClientPort,
		string dataHandlerClassName)
	{
		m_clientBase->Execute(localClientHost, localClientPort, dataHandlerClassName);
	}

	void UClient::HandleOutput(UdpBuffer & bufferSend)
	{
		m_clientBase->HandleOutput(bufferSend);
	}

	SocketAddr UClient::GetServerAddress(UINT32 index)
	{
		return m_clientBase->GetServerAddress(index);
	}

	bool UClient::AppendServerAddress(SocketAddr & addr)
	{
		return m_clientBase->AppendServerAddress(addr);
	}
}
