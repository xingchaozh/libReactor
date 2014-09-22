#include <stdio.h>
using namespace std;

#pragma comment (lib, "ws2_32")

#define LOCAL_HOST_ADDRESS_TEST (1)

#if LOCAL_HOST_ADDRESS_TEST
#define CLIENT_IP "127.0.0.1" //Local location
#else
#define CLIENT_IP "192.168.0.1" //Local location
#endif

#if LOCAL_HOST_ADDRESS_TEST
#define SERVER_IP "127.0.0.1" //Local location
#else
#define SERVER_IP "192.168.0.2" //Local location
#endif

#include "../Source/IFS/IFS.h"
#include "ClientDemo.h" 
#include "ServerDemo.h"

int main()
{
	IFS::PrintErrors("[%d]Main entry.\n",GetCurrentThreadId_X());
	SocketXO::StartupService();

	printf("1--ClientDemo\n2--ServerDemo\n");
	fflush(stdin);
	int index = 0;
	scanf_s("%d",&index);
	fflush(stdin);
	if(1 == index)
	{
		ClientDemo * clientDemo = new ClientDemo();
		clientDemo->Start(CLIENT_IP,50123,SERVER_IP,10125);

		clientDemo->WartForExit();
	}
	else
	{
		ServerDemo * serverDemo = new ServerDemo();
		serverDemo->Start(SERVER_IP,10125);

		serverDemo->WaitForExit();
	}

	FaultRaise::Instance()->Destroy();

	SocketXO::StopService();

	system("pause");
	
	return 0;
}
