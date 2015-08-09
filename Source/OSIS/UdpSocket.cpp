#include "UdpSocket.h"
#include "SocketHelper.h"

namespace libReactor
{
	UdpSocket::UdpSocket(void)
	{
		Create();
	}

	UdpSocket::~UdpSocket(void)
	{
	}

	void UdpSocket::Create()
	{
		SocketX::Create(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	}

	int UdpSocket::RecvFrom(UdpBuffer & udpBuffer)
	{
		return RecvFrom(udpBuffer.buffer.message, MAX_DGRAM_BUFFER_SIZE, udpBuffer.sockAddr);
	}

	int UdpSocket::RecvFrom(UCHAR8 * ptr, int len, SocketAddr & socketAddr)
	{
		struct sockaddr_in addr;
		int len_addr = sizeof(addr);

		int ret = RecvFrom(ptr, len, (sockaddr *)&addr, &len_addr);
		socketAddr = SocketHelper::GetSockAddr(addr);
		return ret;
	}

	int UdpSocket::RecvFrom(UCHAR8 * ptr, int len, sockaddr * from, int * fromlen)
	{
		return recvfrom(socket_, (char*)ptr, len, 0, from, fromlen);
	}

	int UdpSocket::SendTo(UdpBuffer & udpBuffer)
	{
		return SendTo(udpBuffer.buffer.message, udpBuffer.buffer.length, udpBuffer.sockAddr);
	}

	int UdpSocket::SendTo(UCHAR8 * ptr, int len, SocketAddr & socketAddr)
	{
		sockaddr_in to = SocketHelper::GetStdSockAddr(socketAddr);
		int tolen = sizeof(to);
		return SendTo(ptr, len, (sockaddr *)&to, tolen);
	}

	int UdpSocket::SendTo(UCHAR8 * ptr, int len, sockaddr * to, int tolen)
	{
		return sendto(socket_, (char*)ptr, len, 0, to, tolen);
	}
}
