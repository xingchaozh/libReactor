#include "ClientDemo.h" 

ClientDemo::ClientDemo(void)
{
	udpClientConnector_ = NULL;
}

ClientDemo::~ClientDemo(void)
{
	if (NULL != udpClientConnector_)
	{
		delete udpClientConnector_;
	}
}

void ClientDemo::Start(string localClientHost,
					  int localClientPort,
					  string remoteServerHost,
					  int remoteServerPort)
{
	SocketXO::StartupService();
	Sleep(1000);

	udpClientConnector_ = new UClientConnector();
	udpClientConnector_->Initialize(localClientHost,localClientPort,remoteServerHost,remoteServerPort);
	udpClientConnector_->SetTimeOut(50);
	udpClientConnector_->SetDataHanler(NULL);
	udpClientConnector_->Start();

	char buffer[]="Focus on the user and all else will follow.Since the beginning, we?¡¥ve focused on providing the best user experience possible.\n";
	printf("%s\n",buffer);

	UdpBuffer bufferSend;
	memset(bufferSend.buffer.message,0,MAX_DGRAM_BUFFER_SIZE);
	memcpy(bufferSend.buffer.message,buffer,strlen(buffer));
	bufferSend.buffer.length = strlen(buffer);
	bufferSend.sockAddr = udpClientConnector_->GetServerAddr();

	while (true)
	{
		udpClientConnector_->HandleOutput(bufferSend);
		Sleep(70);
	}
	SocketXO::StopService();
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 