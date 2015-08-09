#pragma once

#include "../Common/Common.h"

#include <string>
using namespace std;

namespace libReactor
{
	typedef enum _SocketType
	{
		SOCKET_TYPE_UNKNOWN,
		SOCKET_TYPE_UDP,
		SOCKET_TYPE_TCP
	}SokectType;

	class SocketX
	{
	public:
		SocketX(void);
	public:
		virtual ~SocketX(void);
	public:
		virtual void Create(int af, int type, int protocol);
		virtual void Create() = 0;
		int Bind(sockaddr * name);
		int Bind(SocketAddr & addr);
		int Bind(string host, int port);
		int IsReadable(int timeOut);
		void Close();
	protected:
		int IsReadable(int socketId, int * errorCode, int timeOut);
		void FD_ZERO_X(fd_set * fds);
		void FD_SET_X(SOCKET sock, fd_set * fds);
		int FD_ISSET_X(SOCKET sock, fd_set * fds);
		int Select(int nfds, fd_set * readfds, fd_set * writefds, fd_set * exceptfds, timeval * timeout);
	protected:
		SOCKET socket_;
	};
}
