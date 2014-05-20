#include "UdpServer.h"

UdpServer::UdpServer(void):m_serverAccepter(NULL)
{
}

UdpServer::~UdpServer(void)
{
	if(NULL != m_serverAccepter)
	{
		m_serverAccepter->SetEnable(false);
		m_serverAccepter->WaitForExit();
	}

	vector<UdpDataProcesser *>::iterator i = m_vecDataProcesser.begin();
	for (; i != m_vecDataProcesser.end(); i++)
	{
		(*i)->SetEnable(false);
		(*i)->WaitForExit();
	}
}

void UdpServer::Start(string localHost,  //Local host location
					  int localPort)     //Local host port
{
	//Create the communication server thread
	m_serverAccepter = new UdpServerAccepter();
	m_serverAccepter->Initialize(localHost,localPort);
	m_serverAccepter->Start();

	//create the data process thread list
	const int NUM_DATA_PROCESSER = 2;
	for (int i = 0; i < NUM_DATA_PROCESSER; i++)
	{
		UdpDataProcesser * dataProcesser = new UdpDataProcesser(m_serverAccepter);
		dataProcesser->Start();
		m_vecDataProcesser.push_back(dataProcesser);
	}

	//exit process
	m_serverAccepter->WaitForExit();
	vector<UdpDataProcesser *>::iterator i = m_vecDataProcesser.begin();
	for (; i != m_vecDataProcesser.end(); i++)
	{
		(*i)->SetEnable(false);
		(*i)->WaitForExit();
	}
}
