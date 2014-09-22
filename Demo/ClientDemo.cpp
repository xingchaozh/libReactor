#include "ClientDemo.h" 


ClientDemo::ClientDemo(void)
{

}
ClientDemo::~ClientDemo(void)
{

}

void ClientDemo::Start(string localClientHost,
					   int localClientPort,
					   string remoteServerHost,
					   int remoteServerPort)
{
	ReflectionRegister<UdpClientDataHandler>::Register();
	Execute(localClientHost,localClientPort, typeid(UdpClientDataHandler).name());

	//Client Request process
	char buffer[]="Focus on the user and all else will follow.Since the beginning, we've focused on providing the best user experience possible.\n";
	printf("%s\n",buffer);

	UdpBuffer bufferSend;
	memset(bufferSend.buffer.message,0,MAX_DGRAM_BUFFER_SIZE);
	memcpy(bufferSend.buffer.message,buffer,strlen(buffer));
	bufferSend.buffer.length = strlen(buffer);
	bufferSend.sockAddr = SocketXO::GetSockAddr(remoteServerHost,remoteServerPort);

	while (true)
	{
		udpClientConnector_->HandleOutput(bufferSend);
		Sleep(70);
	}
}

//////////////////////////////////////////////////////////////////////////
//UdpClientDataHandler
UdpClientDataHandler::UdpClientDataHandler()
{
}
UdpClientDataHandler::~UdpClientDataHandler(void)
{
}

void UdpClientDataHandler::DataHanle(UdpBuffer & udpBuffer)
{
	IFS::PrintErrors("%s\n",udpBuffer.buffer.message);
}


//
//
//ClientDemo2::ClientDemo2(void)
//{
//	udpClientConnector_ = NULL;
//}
//
//ClientDemo2::~ClientDemo2(void)
//{
//	if (NULL != udpClientConnector_)
//	{
//		delete udpClientConnector_;
//	}
//}
//
//void ClientDemo2::Start(string localClientHost,
//						int localClientPort,
//						string remoteServerHost,
//						int remoteServerPort)
//{
//	udpClientConnector_ = new UClientConnector();
//	udpClientConnector_->Initialize(localClientHost,localClientPort);
//	udpClientConnector_->SetTimeOut(50);
//	udpClientConnector_->SetDataHanler(NULL);
//	udpClientConnector_->Start();
//
//	char buffer[]="Focus on the user and all else will follow.Since the beginning, we?¡¥ve focused on providing the best user experience possible.\n";
//	printf("%s\n",buffer);
//
//	UdpBuffer bufferSend;
//	memset(bufferSend.buffer.message,0,MAX_DGRAM_BUFFER_SIZE);
//	memcpy(bufferSend.buffer.message,buffer,strlen(buffer));
//	bufferSend.buffer.length = strlen(buffer);
//	bufferSend.sockAddr = SocketXO::GetSockAddr(remoteServerHost,remoteServerPort);
//
//	while (true)
//	{
//		udpClientConnector_->HandleOutput(bufferSend);
//		Sleep(70);
//	}
//}
//
//

