#include "UdpClient.h"

UdpClient::UdpClient(void)
{
	udpClientConnector_ = NULL;
}

UdpClient::~UdpClient(void)
{
	if (NULL != udpClientConnector_)
	{
		delete udpClientConnector_;
	}
}

void UdpClient::Start(string localHost,
					  int localPort,
					  string remoteHost,
					  int remotePort)
{
	udpClientConnector_ = new UdpClientConnector();
	udpClientConnector_->Initialize(localHost,localPort,remoteHost,remotePort);
	udpClientConnector_->SetTimeOut(50);
	udpClientConnector_->Start();

	char buffer[]="Focus on the user and all else will follow.Since the beginning, we¡¯ve focused on providing the best user experience possible.\n";
	printf("%s\n",buffer);

	UdpBufferRev bufferSend;
	memset(bufferSend.bufferRev.buffer,0,MAX_DGRAM_BUFFER_SIZE);
	memcpy(bufferSend.bufferRev.buffer,buffer,strlen(buffer));
	bufferSend.bufferRev.length = strlen(buffer);
	bufferSend.fromAddr = udpClientConnector_->GetServerAddr();

	while (true)
	{
		udpClientConnector_->GetBufferQueue()->EnQueue(bufferSend);
		Sleep(50);
	}
}
