#pragma once

#include "Common.h"

#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <sys/timeb.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include <vector>

namespace libReactor
{
	class Utils
	{
	public:
		Utils(void);
		virtual ~Utils(void);

		static void split(std::string& src, std::string& delim, std::vector< std::string > & ret);

		static void StringReplace(string & str, string searchString, string replaceString);
		static std::string& trim(std::string &s);

		static long Str2Long(string buff);
		static string Long2Str(const long n);

		static bool IsDigit(string & str);
		static int GetDigitLen(long x);

		static string GetFirstWord(string str);

		static string GetTimeNow();

		template<typename T>
		static string ValueToStr(T value)
		{
			ostringstream ost;
			ost << value;
			return ost.str();
		}
	};
}
