#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <sys/timeb.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "../Common/Common.h"

namespace libReactor
{
	typedef map<string, string> ConfigMap;
	typedef map<string, string>::iterator ConfigMapIterator;
	typedef map<string, string>::const_iterator ConfigMapConstIterator;

	class ConfigHelper
	{
	public:
		ConfigHelper();
		~ConfigHelper();
	public:
		static void LoadConfig(ConfigMap & mapConfig, string strPath);

	private:
		static bool Load(vector<string> & vecParas, string strPath);
		static bool Load(vector<string> & vecParas, string strPath, vector<string> & vecSkip);
		static bool Load(vector<string> & vecParas, string strPath, string strContain);
	};
}
