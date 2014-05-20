#include "UdpClient.h"

UdpClient::UdpClient(void)
{
	m_udpClientConnector = NULL;
}

UdpClient::~UdpClient(void)
{
	if (NULL != m_udpClientConnector)
	{
		delete m_udpClientConnector;
	}
}

void UdpClient::Start(string localHost,
					  int localPort,
					  string remoteHost,
					  int remotePort)
{

	m_udpClientConnector = new UdpClientConnector();
	m_udpClientConnector->Initialize(localHost,localPort,remoteHost,remotePort);
	m_udpClientConnector->SetTimeOut(50);
	m_udpClientConnector->Start();

	char buffer[]="Focus on the user and all else will follow.Since the beginning, we¡¯ve focused on providing the best user experience possible.\n";
	printf("%s\n",buffer);

	UdpBufferRev bufferSend;
	memset(bufferSend.bufferRev.buffer,0,MAX_DGRAM_BUFFER_SIZE);
	memcpy(bufferSend.bufferRev.buffer,buffer,strlen(buffer));
	bufferSend.bufferRev.length = strlen(buffer);
	bufferSend.fromAddr = m_udpClientConnector->GetServerAddr();

	while (true)
	{
		m_udpClientConnector->GetBufferQueue()->EnQueue(&bufferSend);
		Sleep(500);
	}
}
