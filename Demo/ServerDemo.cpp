#include "ServerDemo.h"

#include "UServerDataHandler.h"

ServerDemo::ServerDemo(void):serverAccepter_(NULL)
{
}

ServerDemo::~ServerDemo(void)
{
	if(NULL != serverAccepter_)
	{
		serverAccepter_->SetEnable(false);
		serverAccepter_->WaitForExit();
	}

	vector<UDataProcesser *>::iterator i = vecDataProcesser_.begin();
	for (; i != vecDataProcesser_.end(); i++)
	{
		(*i)->SetEnable(false);
		(*i)->WaitForExit();
	}
}

void ServerDemo::Start(string serverHost,  //Local host location
					  int serverPort, int remoteClientPort)     //Local host port
{
	
	SocketXO::StartupService();
	Sleep(1000);

	//Create the communication server thread
	serverAccepter_ = new UServerAccepter();
	serverAccepter_->Initialize(serverHost,serverPort);
	serverAccepter_->SetTimeOut(100);
	serverAccepter_->Start();

	//create the data process thread list
	const int NUM_DATA_PROCESSER = 2;
	for (int i = 0; i < NUM_DATA_PROCESSER; i++)
	{
		UDataProcesser * dataProcesser = new UDataProcesser(serverAccepter_);
		//create the data handler for dataProcesser
		UdpServerDataHandler * udpServerDataHandler = new UdpServerDataHandler(serverAccepter_);
		dataProcesser->SetDataHanler(udpServerDataHandler);
		dataProcesser->Start();

		vecDataProcesser_.push_back(dataProcesser);
	}

	
	//exit process
	serverAccepter_->WaitForExit();
	vector<UDataProcesser *>::iterator i = vecDataProcesser_.begin();
	for (; i != vecDataProcesser_.end(); i++)
	{
		(*i)->SetEnable(false);
		(*i)->WaitForExit();
	}

	SocketXO::StopService();
}
