#pragma once

#include "SocketX.h"

namespace libReactor
{
	class UdpSocket :
		public SocketX
	{
	public:
		UdpSocket(void);
		~UdpSocket(void);
	public:
		int RecvFrom(UdpBuffer & udpBuffer);
		int SendTo(UdpBuffer & udpBuffer);
	protected:
		void Create();
		int RecvFrom(UCHAR8 * ptr, int len, sockaddr * from, int * fromlen);
		int RecvFrom(UCHAR8 * ptr, int len, SocketAddr & socketAddr);
		int SendTo(UCHAR8 * ptr, int len, sockaddr * to, int tolen);
		int SendTo(UCHAR8 * ptr, int len, SocketAddr & socketAddr);
	};
}
