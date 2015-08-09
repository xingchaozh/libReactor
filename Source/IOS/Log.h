#pragma once

#include "../Common/Common.h"

#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
using namespace std;

namespace libReactor
{
	class Log
	{
	public:
		Log();
		~Log();
		virtual bool Open(string sFileName);
		virtual void Close();
		virtual void Enable();
		virtual void Disable();
		virtual int Size();

		virtual void Write(const char* buf, unsigned int size) = 0;
	public:
		template<typename T>
		static string ValueToStr(T value)
		{
			ostringstream ost;
			ost << value;
			return ost.str();
		}
		string GetCurTimeStr();
	protected:
		FILE * outputFile_;
		bool enabled_;
	};
}
