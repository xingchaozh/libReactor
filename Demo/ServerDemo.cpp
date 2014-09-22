#include "ServerDemo.h"

ServerDemo::ServerDemo(void)
{
}

ServerDemo::~ServerDemo(void)
{
}

void ServerDemo::Start(string localServerHost, int localServerPort)
{
	ReflectionRegister<UdpServerDataHandler>::Register();
	Execute(localServerHost,localServerPort, typeid(UdpServerDataHandler).name());
}


//////////////////////////////////////////////////////////////////////////
//UdpServerDataHandler
UdpServerDataHandler::UdpServerDataHandler()
{
	udpServerAccepter_ = NULL;
}

UdpServerDataHandler::~UdpServerDataHandler(void)
{
}

void UdpServerDataHandler::DataHanle(UdpBuffer & udpBuffer)
{
	//Process
	printf("Rev form %s:%d, length = %d\n",udpBuffer.sockAddr.strAddress,udpBuffer.sockAddr.port,udpBuffer.buffer.length);
	string strAck = "Ack from Server";

	//Send Result back to Client.
	UdpBuffer udpBufferSend;
	memset(&udpBufferSend,0,sizeof(UdpBuffer));
	memcpy(udpBufferSend.buffer.message,strAck.c_str(),strAck.length());
	udpBufferSend.buffer.length = strAck.length();
	udpBufferSend.sockAddr = SocketXO::GetSockAddr(udpBuffer.sockAddr.strAddress,udpBuffer.sockAddr.port);
	if(NULL != udpServerAccepter_)
	{
		udpServerAccepter_->HandleOutput(udpBufferSend);
	}
}
