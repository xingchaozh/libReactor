/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : Log.h
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#ifndef _LOG_H_
#define _LOG_H_

#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
using namespace std;

class Log
{
public:
	Log();
	~Log();
	virtual bool Open(string sFileName);
	void Close();
	void Enable();
	void Disable();
	int Size();
	string GetCurTimeStr();
protected:
	template<typename T>
	string ValueToStr(T value)
	{
		ostringstream ost;
		ost << value;
		return ost.str();
	}
protected:
	FILE * m_logFile;
	bool m_bLogEnabled;
};

#endif