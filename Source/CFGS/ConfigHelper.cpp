#include "ConfigHelper.h"
#include "../Common/Utils.h"

namespace libReactor
{
	ConfigHelper::ConfigHelper()
	{
	}

	ConfigHelper::~ConfigHelper()
	{
	}

	void ConfigHelper::LoadConfig(ConfigMap & mapConfig, string strPath)
	{
		vector<string> vecParas;
		vector<string> vecSkip;
		vecSkip.push_back("#");
		vecSkip.push_back(";");
		Load(vecParas, strPath, vecSkip);

		vector<string> vecVariable;
		string delim = "=";
		for (auto i = vecParas.begin(); i != vecParas.end(); i++)
		{
			vecVariable.clear();
			libReactor::Utils::split(*i, delim, vecVariable);
			if (vecVariable.size() == 2)
			{
				mapConfig.insert(make_pair(libReactor::Utils::trim(vecVariable[0]),
					libReactor::Utils::trim(vecVariable[1])));
			}
		}
	}

	bool ConfigHelper::Load(vector<string> & vecParas, string strPath)
	{
		std::string buff;

		std::ifstream DbSyParmsCfg(strPath.c_str());
		if (!DbSyParmsCfg)
		{
			printf("Error: The file <%s> can not be open!\n", strPath.c_str());
			return false;
		}

		while (!DbSyParmsCfg.eof())
		{
			//Get a line
			std::getline(DbSyParmsCfg, buff, '\n');
			//Skip comment and blank line
			if (buff != "")//(buff.find('#') == -1 && buff != "")
			{
				vecParas.push_back(buff);
			}
		}
		return true;
	}

	bool ConfigHelper::Load(vector<string> & vecParas, string strPath, vector<string> & vecSkip)
	{
		std::string buff;

		std::ifstream DbCfg(strPath.c_str());
		if (!DbCfg)
		{
			printf("Error: The file <%s> can not be open!\n", strPath.c_str());
			return false;
		}

		while (!DbCfg.eof())
		{
			//Get a line
			std::getline(DbCfg, buff, '\n');
			//Skip
			if (vecSkip.size() == 0 || find(vecSkip.begin(), vecSkip.end(), libReactor::Utils::GetFirstWord(buff)) == vecSkip.end())
			{
				if (buff != "")
				{
					vecParas.push_back(buff);
				}
			}
		}
		return true;
	}

	bool ConfigHelper::Load(vector<string> & vecParas, string strPath, string strContain)
	{
		std::string buff;

		std::ifstream DbCfg(strPath.c_str());
		if (!DbCfg)
		{
			printf("Error: The <%s> can't be open, please check whether the file exists!\n", strPath.c_str());
			return false;
		}

		while (!DbCfg.eof())
		{
			//Get a line
			std::getline(DbCfg, buff, '\n');
			//Read
			size_t pos = 0;
			if (buff.size() > strContain.size() && (pos = buff.find(strContain)) != string::npos)
			{
				if (buff != "")
				{
					vecParas.push_back(buff.substr(pos + strContain.size()));
				}
			}
		}
		return true;
	}
}
