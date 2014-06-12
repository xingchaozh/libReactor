#include "UdpServer.h"

#include "UdpServerDataHandler.h"

UdpServer::UdpServer(void):serverAccepter_(NULL)
{
}

UdpServer::~UdpServer(void)
{
	if(NULL != serverAccepter_)
	{
		serverAccepter_->SetEnable(false);
		serverAccepter_->WaitForExit();
	}

	vector<UdpDataProcesser *>::iterator i = vecDataProcesser_.begin();
	for (; i != vecDataProcesser_.end(); i++)
	{
		(*i)->SetEnable(false);
		(*i)->WaitForExit();
	}
}

void UdpServer::Start(string localServerHost,  //Local host location
					  int localServerPort, int remoteClientPort)     //Local host port
{
	//Create the communication server thread
	serverAccepter_ = new UdpServerAccepter();
	serverAccepter_->Initialize(localServerHost,localServerPort);
	serverAccepter_->SetTimeOut(1000);
	serverAccepter_->Start();

	//create the data process thread list
	const int NUM_DATA_PROCESSER = 2;
	for (int i = 0; i < NUM_DATA_PROCESSER; i++)
	{
		UdpDataProcesser * dataProcesser = new UdpDataProcesser(serverAccepter_);
		//create the data handler for dataProcesser
		UdpServerDataHandler * udpServerDataHandler = new UdpServerDataHandler(localServerHost,remoteClientPort);
		dataProcesser->SetDataHanler(udpServerDataHandler);
		dataProcesser->Start();
		vecDataProcesser_.push_back(dataProcesser);
	}

	//exit process
	serverAccepter_->WaitForExit();
	vector<UdpDataProcesser *>::iterator i = vecDataProcesser_.begin();
	for (; i != vecDataProcesser_.end(); i++)
	{
		(*i)->SetEnable(false);
		(*i)->WaitForExit();
	}
}
