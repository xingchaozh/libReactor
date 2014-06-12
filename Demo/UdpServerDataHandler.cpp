#include "UdpServerDataHandler.h"


UdpServerDataHandler::UdpServerDataHandler(string localServerHost, int remoteClientPort)
{
	localServerHost_ = localServerHost;
	remoteClientPort_ = remoteClientPort;

	socket_ = new UdpSocketXO();
	socket_->Bind(localServerHost_,0);
}

UdpServerDataHandler::~UdpServerDataHandler(void)
{
	delete socket_;
}

void UdpServerDataHandler::DataHanle(UdpBuffer & udpBuffer)
{
	//TODO
	//Process
#if LIB_REACTOR_DEBUG
	static int index = 0;
	printf("UdpServerDataHandler::DataHanle: (%d) Rev msg from (%s:%d) : length:%d\n",index++,udpBuffer.sockAddr.strAddress,udpBuffer.sockAddr.port,udpBuffer.buffer.length);
#endif
	//TODO
	//Process Result
	string strAck = "Ack from Server";

	//Send Result back to Client.
	if (0 != remoteClientPort_)
	{
		UdpBuffer udpBufferSend;
		memset(&udpBufferSend,0,sizeof(UdpBuffer));
		memcpy(udpBufferSend.buffer.message,strAck.c_str(),strAck.length());
		udpBufferSend.buffer.length = strAck.length();
		udpBufferSend.sockAddr = SocketXO::GetSockAddr(udpBuffer.sockAddr.strAddress,remoteClientPort_);
		socket_->SendTo(udpBufferSend);
	}
}

void UdpServerDataHandler::SetRemotePort(int remotePort)
{
	remoteClientPort_ = remotePort;
}
