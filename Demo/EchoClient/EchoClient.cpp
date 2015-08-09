// EchoClient.cpp : Defines the entry point for the console application.
//

#include "EchoClient.h"

void EchoClient::Start(string localClientHost, int localClientPort,
					   string remoteServerHost, int remoteServerPort)
{
	Execute(localClientHost,localClientPort, typeid(UdpClientDataHandler).name());

	//Client Request
	UdpBuffer bufferSend;
	while (true)
	{
		IFS::PrintErrors("Enter your message:");
		std::string msg;
		std::cin >> msg;
		if (msg == "q")
		{
			break;
		}

		memset(bufferSend.buffer.message, 0, MAX_DGRAM_BUFFER_SIZE);
		memcpy(bufferSend.buffer.message, msg.c_str(), msg.length());
		bufferSend.buffer.length = msg.length();
		bufferSend.sockAddr = SocketHelper::GetSockAddr(remoteServerHost,remoteServerPort);

		HandleOutput(bufferSend);
		Sleep(50);
	}
}

AutoReflectionRegister(UdpClientDataHandler)
	void UdpClientDataHandler::DataHanle(UdpBuffer & udpBuffer)
{
	static int index = 0;
	IFS::PrintErrors("[%d] %s\n",index++, udpBuffer.buffer.message);
}
