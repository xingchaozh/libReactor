#pragma once

#include "../Source/UdpServerAccepter.h"
#include "../Source/UdpDataProcesser.h"
#include <vector>
using namespace std;

class UdpServer
{
public:
	UdpServer(void);
	~UdpServer(void);
public:
	void Start(string localHost, int localPort);
public:
	UdpServerAccepter * serverAccepter_;
	vector<UdpDataProcesser *> vecDataProcesser_;
};
