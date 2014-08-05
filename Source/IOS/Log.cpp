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
	enabled_ = true;
}

Log::~Log()
{
	Close();
}

bool Log::Open(string sFileName)
{
	fopen_s(&outputFile_,sFileName.c_str(),"w");

	if( !outputFile_ )
	{
		return false;
	}
	return true;
}

void Log::Close()
{
	fclose(outputFile_);
}

void Log::Enable()
{
	enabled_ = true;
}

void Log::Disable()
{
	enabled_ = false;
}

int Log::Size()
{
	FILE* fp = outputFile_;
	fseek(fp,0,SEEK_END);
	return ftell(fp);
}

string Log::GetCurTimeStr()
{
	time_t tNowTime;
	time(&tNowTime);
	tm* tLocalTime = NULL;//tm* tLocalTime = localtime(&tNowTime);
	localtime_s(tLocalTime,&tNowTime);

	string strDateTime = ValueToStr(tLocalTime->tm_year+1900) + "-" +
		ValueToStr(tLocalTime->tm_mon+1)     + "-" +
		ValueToStr(tLocalTime->tm_mday)      + " " +
		ValueToStr(tLocalTime->tm_hour)      + "-" +
		ValueToStr(tLocalTime->tm_min)       + "-" +
		ValueToStr(tLocalTime->tm_sec);
	return strDateTime;
}
