#include "EchoServer.h"
#include "../../Source/IFS/ReflectionX.h"

void EchoServerDemo::Start(string localServerHost, int localServerPort)
{
	Execute(localServerHost,localServerPort, typeid(UdpServerDataHandler).name());
}

AutoReflectionRegister(UdpServerDataHandler)
void UdpServerDataHandler::DataHanle(UdpBuffer & udpBuffer)
{
	//Process
	static int index = 0;
	udpBuffer.buffer.message[udpBuffer.buffer.length] = '\0';
	IFS::PrintErrors("[%d] Rev form %s:%d: %s\n",index++,udpBuffer.sockAddr.strAddress,udpBuffer.sockAddr.port,udpBuffer.buffer.message);
	string strAck = (char*)udpBuffer.buffer.message;

	//Echo message back to Client.
	UdpBuffer udpBufferSend;
	memset(&udpBufferSend,0,sizeof(UdpBuffer));
	memcpy(udpBufferSend.buffer.message, strAck.c_str(),strAck.length());
	udpBufferSend.buffer.length = strAck.length();
	udpBufferSend.sockAddr = SocketHelper::GetSockAddr(udpBuffer.sockAddr.strAddress,udpBuffer.sockAddr.port);
	HandleOutput(udpBufferSend);
}
