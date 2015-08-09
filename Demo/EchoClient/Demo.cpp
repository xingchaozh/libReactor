#include "EchoClient.h"

#include <iostream>
using namespace std;
using namespace libReactor;
#pragma comment (lib, "ws2_32")

int main()
{
	SocketHelper socketHelper;

	std::cout << "Server demo start(Enter 'q' to exit)." << std::endl;
	EchoClient echoClient;
	echoClient.Start("127.0.0.1", 50123, "127.0.0.1", 10125);

	// Or run in a dedicated thread like this:
	// libReactor::Thread::RunAsThread(std::bind(&EchoClient::Start, &echoClient, "127.0.0.1", 50123, "127.0.0.1", 10125));
	return 0;
}
