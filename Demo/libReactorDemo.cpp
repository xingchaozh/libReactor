
#include <stdio.h>

#pragma comment (lib, "ws2_32")

#define SERVER_IP "127.0.0.1" //Server location
#define SERVER_PORT 5208 //Listen port

#include "UdpServer.h"
#include "UdpClient.h"

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
		flushall();
		int index;
		scanf("%d",&index);
		switch(index)
		{
		case 1:
			{
				printf("The Udp Server Demo:\n");
				UdpServer Server;
				Server.Start(SERVER_IP,SERVER_PORT);
				break;
			}
		case 2:
			{
				printf("The Udp Client Demo:\n");
				UdpClient client;
				client.Start(SERVER_IP,0,SERVER_IP,SERVER_PORT);
				break;
			}
		case 0:
			{
				flag = -1;
				while(flag == -1)
				{
					printf("Exit the socket demo?y/n ");
					flushall();
					char c;
					scanf("%c",&c);
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
