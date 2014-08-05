#include "UServerDataHandler.h"


UdpServerDataHandler::UdpServerDataHandler(UServerAccepter * udpServerAccepter)
{
	udpServerAccepter_ = udpServerAccepter;
}

UdpServerDataHandler::~UdpServerDataHandler(void)
{
}

void UdpServerDataHandler::DataHanle(UdpBuffer & udpBuffer)
{
	//TODO
	//Process
	string strAck = "Ack from Server";

	//Send Result back to Client.
	UdpBuffer udpBufferSend;
	memset(&udpBufferSend,0,sizeof(UdpBuffer));
	memcpy(udpBufferSend.buffer.message,strAck.c_str(),strAck.length());
	udpBufferSend.buffer.length = strAck.length();
	udpBufferSend.sockAddr = SocketXO::GetSockAddr(udpBuffer.sockAddr.strAddress,udpBuffer.sockAddr.port);
	udpServerAccepter_->HandleOutput(udpBufferSend);
}
