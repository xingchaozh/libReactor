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
	static const int BUFFER_SIZE=1024*1;//Bytes
	static const int MAX_SINGLE_LOG_FILE_SIZE = 1024 * 1024 * 30;//Bytes
	char m_buffer[BUFFER_SIZE];
	int m_current;

	string m_sFileName;
	bool m_bAtuoSplitFile;
};
