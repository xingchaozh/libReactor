#pragma once

#include "../Source/NETS/UServerAccepter.h"
#include "../Source/NETS/UDataProcesser.h"

#include <vector>
using namespace std;

class ServerDemo
{
public:
	ServerDemo(void);
	~ServerDemo(void);
public:
	void Start(string localServerHost, int localServerPort, int remoteClientPort);
public:
	UServerAccepter * serverAccepter_;
	vector<UDataProcesser *> vecDataProcesser_;
};
