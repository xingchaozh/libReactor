#include "EchoServer.h"

#include <iostream>
using namespace std;
using namespace libReactor;
#pragma comment (lib, "ws2_32")

int main()
{
	SocketHelper socketHelper;

	std::cout << "Server demo start(Enter 'q' to exit)." << std::endl;
	EchoServerDemo serverDemo;
	serverDemo.Start("127.0.0.1", 10125);

	std::string exit;
	while (exit != "q")
	{
		std::cin >> exit;
	}
	FaultRaise::Instance()->Destroy();
	return 0;
}
