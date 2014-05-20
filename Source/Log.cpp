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
	m_bLogEnabled = true;
}

Log::~Log()
{
	Close();
}

bool Log::Open(string sFileName)
{
	m_logFile = fopen(sFileName.c_str(),"w");

	if( !m_logFile )
	{
		return false;
	}
	return true;
}

void Log::Close()
{
	fclose(m_logFile);
}

void Log::Enable()
{
	m_bLogEnabled = true;
}

void Log::Disable()
{
	m_bLogEnabled = false;
}

int Log::Size()
{
	FILE* fp = m_logFile;
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
