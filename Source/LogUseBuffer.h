/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : LogUseBuffer.h
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#pragma once
#include "log.h"

class LogUseBuffer :
	public Log
{
public:
	LogUseBuffer(void);
	virtual ~LogUseBuffer(void);

public:
	bool Open(string sFileName, bool bWithATime = false);
	void Write(const char* buf, unsigned int size);
	void WriteLn();
	void Write(string str);
	void WirteImmediately(const char* buf, unsigned int size);

private:
	void Flush();

private:
	char buffer_[LOG_BUFFER_SIZE];
	int current_;

	string fileName_;
	bool autoSplitFile_;
};
