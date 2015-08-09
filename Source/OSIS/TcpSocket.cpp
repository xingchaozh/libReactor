#include "TcpSocket.h"

namespace libReactor
{
	TcpSocket::TcpSocket(void)
	{
		Create();
	}

	TcpSocket::~TcpSocket(void)
	{
	}

	void TcpSocket::Create()
	{
		SocketX::Create(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}
}
