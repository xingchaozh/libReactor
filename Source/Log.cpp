/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : Log.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "Log.h"
Log::Log()
{
	logEnabled_ = true;
}

Log::~Log()
{
	Close();
}

bool Log::Open(string sFileName)
{
	logFile_ = fopen(sFileName.c_str(),"w");

	if( !logFile_ )
	{
		return false;
	}
	return true;
}

void Log::Close()
{
	fclose(logFile_);
}

void Log::Enable()
{
	logEnabled_ = true;
}

void Log::Disable()
{
	logEnabled_ = false;
}

int Log::Size()
{
	FILE* fp = logFile_;
	fseek(fp,0,SEEK_END);
	return ftell(fp);
}

string Log::GetCurTimeStr()
{
	time_t tNowTime;
	time(&tNowTime);
	tm* tLocalTime = localtime(&tNowTime);

	string strDateTime = ValueToStr(tLocalTime->tm_year+1900) + "-" +
		ValueToStr(tLocalTime->tm_mon+1)     + "-" +
		ValueToStr(tLocalTime->tm_mday)      + " " +
		ValueToStr(tLocalTime->tm_hour)      + "-" +
		ValueToStr(tLocalTime->tm_min)       + "-" +
		ValueToStr(tLocalTime->tm_sec);
	return strDateTime;
}
