#include <stdio.h>
using namespace std;

#pragma comment (lib, "ws2_32")

#define LOCAL_HOST_ADDRESS_TEST 1

#if LOCAL_HOST_ADDRESS_TEST
#define CLIENT_IP "127.0.0.1" //Local location
#else
#define CLIENT_IP "192.168.0.100" //Local location
#endif
#define CLIENT_PORT 6012 //Local Listen port

#if LOCAL_HOST_ADDRESS_TEST
#define SERVER_IP "127.0.0.1" //Local location
#else
#define SERVER_IP "192.168.0.32" //Local location
#endif
#define SERVER_PORT 8012 //Server Listen port

#include "ServerDemo.h"
#include "ClientDemo.h"

int StartApp();

int main()
{
	StartApp();
	return 0;
}

int StartApp()
{
	int flag = 1;
	while(flag == 1)
	{
		printf("******************************************************************\n");
		printf("1. Udp Server  2. Udp Client  \n0. Exit\n");
		printf("Enter the index of the command to start the service.\n");
		int index;
		fflush(stdin);
		scanf_s("%d",&index);
		switch(index)
		{
		case 1:
			{
				printf("The Udp Server Demo:\n");
				ServerDemo Server;
				Server.Start(SERVER_IP,SERVER_PORT,CLIENT_PORT);
				break;
			}
		case 2:
			{
				printf("The Udp Client Demo:\n");
				ClientDemo client;
				client.Start(CLIENT_IP,CLIENT_PORT,SERVER_IP,SERVER_PORT);
				break;
			}
		case 0:
			{
				flag = -1;
				while(flag == -1)
				{
					printf("Exit the socket demo?y/n ");
					char c;
					fflush(stdin);//flushall();
					scanf_s("%c",&c);
					if(c=='Y' || c=='y')
					{
						flag = 0;
					}
					else if(c=='N' || c=='n')
					{
						flag = 1;
					}
					else
					{
						flag = -1;
					}
				}
				break;
			}
		default:break;
		}
	}
	return 0;
}
