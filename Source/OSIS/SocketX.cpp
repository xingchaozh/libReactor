#include "SocketX.h"
#include "SocketHelper.h"

namespace libReactor
{
	SocketX::SocketX(void)
	{
	}

	SocketX::~SocketX(void)
	{
		Close();
	}

	int SocketX::Select(int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, timeval * timeout)
	{
		//int select(int nfds, fd_set * readfds,fd_set * writefds,fd_set * exceptfds,timeval * timeout);
		return select(nfds, readfds, writefds, exceptfds, timeout);
	}

	void SocketX::FD_ZERO_X(fd_set * fds)
	{
		FD_ZERO(fds);
	}

	void SocketX::FD_SET_X(SOCKET sock, fd_set * fds)
	{
		FD_SET(sock, fds);
	}

	int SocketX::FD_ISSET_X(SOCKET sock, fd_set * fds)
	{
		return FD_ISSET(sock, fds);
	}

	void SocketX::Create(int af, int type, int protocol)
	{
		/*
		*first param is protocol family, generally AF_INET for IP internet.
		*second param is type of socket, SOCK_DGRAM is for Data Gram£¨UDP£©, and SOCK_STREAM is for TCP.
		*the last param is communicate protocol. Generally is zero.
		*/
		//SOCKET socket(int af, int type, int protocol);
		//m_socket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
		socket_ = socket(af, type, protocol);
		if (INVALID_SOCKET == socket_)
		{
			printf("socket() faild!\n");
			return;
		}
	}

	int SocketX::Bind(sockaddr * addr)
	{
		int ret = bind(socket_, addr, sizeof(sockaddr));
		if (SOCKET_ERROR == ret)
		{
			printf("bind() faild! code:%d\n", WSAGetLastError());
			Close();
		}
		return ret;
	}

	int SocketX::Bind(SocketAddr & addr)
	{
		return Bind((sockaddr *)&(SocketHelper::GetStdSockAddr(addr)));
	}

	int SocketX::Bind(string host, int port)
	{
		return Bind(SocketHelper::GetSockAddr(host, port));
	}

	void SocketX::Close()
	{
		closesocket(socket_);
	}

	int SocketX::IsReadable(int timeOut)
	{
		int errorCode;
		return IsReadable(socket_, &errorCode, timeOut);
	}

	int SocketX::IsReadable(int socketId, int * errorCode, int timeOut) // milliseconds
	{
		fd_set socketReadSet;

		//Initialize the set
		FD_ZERO_X(&socketReadSet);

		//put m_socket->GetSocket() into the set
		FD_SET_X(socketId, &socketReadSet);

		struct timeval tvTimeout;
		if (timeOut > 0)
		{
			tvTimeout.tv_sec = timeOut / 1000;
			tvTimeout.tv_usec = (timeOut % 1000) * 1000;
		}
		else
		{
			tvTimeout.tv_sec = 0;
			tvTimeout.tv_usec = 0;
		}

		//check the status of the socket I/O
		int ret = SocketX::Select(socketId + 1, &socketReadSet, 0, 0, &tvTimeout);
		if (ret == SOCKET_ERROR)
		{
			*errorCode = 1;
			return 0;
		}

		*errorCode = 0;
		return FD_ISSET_X(socketId, &socketReadSet) != 0;
	}
}
