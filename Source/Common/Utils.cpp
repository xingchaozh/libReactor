#include "Utils.h"

namespace libReactor
{
	Utils::Utils(void)
	{
	}


	Utils::~Utils(void)
	{
	}

	void Utils::split(std::string& src, std::string& delim, std::vector< std::string > & ret)
	{
		size_t last = 0;
		size_t index = src.find(delim, last);
		while (index != std::string::npos)
		{
			ret.push_back(src.substr(last, index - last));
			last = index + 1;
			index = src.find(delim, last);
		}
		if (index - last > 0)
		{
			ret.push_back(src.substr(last, index - last));
		}
	}

	void Utils::StringReplace(string & str, string searchString, string replaceString)
	{
		string::size_type pos = 0;

		while ((pos = str.find(searchString, pos)) != string::npos)
		{
			str.replace(pos, searchString.size(), replaceString);
			pos++;
		}
	}

	std::string & Utils::trim(std::string &s)
	{
		if (s.empty())
		{
			return s;
		}
		s.erase(0, s.find_first_not_of(" "));
		s.erase(s.find_last_not_of(" ") + 1);
		return s;
	}

	long Utils::Str2Long(string buff)
	{
		long result = -1;
		std::istringstream linestr(buff);
		linestr >> result;
		return result;
	}

	string Utils::Long2Str(const long n)
	{
		std::stringstream newstr;
		newstr << n;
		return newstr.str();
	}

	bool Utils::IsDigit(string & str)
	{
		int len = str.length();
		for (int i = 0; i < len; i++)
		{
			if ((!(str.at(0) == '-' && i == 0)) &&
				(!(str.at(0) == '.' && i != 0)) &&
				(str.at(i) > '9' || str.at(i) < '0'))
			{
				return false;
			}
		}
		return true;
	}

	int Utils::GetDigitLen(long x)//cout<<x<<"µÄÎ»Êý£º"<<a<<endl;
	{
		int a = 0;
		long n = x;
		while (n >= 10)
		{
			++a;
			n /= 10;
		}
		++a;
		return a;
	}

	string Utils::GetFirstWord(string str)
	{
		int index = (int)str.find_first_of(" ");
		return str.substr(0, index);
	}

	string Utils::GetTimeNow()//get current time string(ms)
	{
		timeb t;
		ftime(&t);
		tm * tLocalTime = new tm();
		//localtime_s(tLocalTime,&t.time);

		string strDateTime = Long2Str(tLocalTime->tm_year + 1900) + "_" +
			Long2Str(tLocalTime->tm_mon + 1) + "_" +
			Long2Str(tLocalTime->tm_mday) + "_" +
			Long2Str(tLocalTime->tm_hour) + "_" +
			Long2Str(tLocalTime->tm_min) + "_" +
			Long2Str(tLocalTime->tm_sec);

		delete tLocalTime;
		return strDateTime;
	}
}
