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

class BufferLogger :
	public Log
{
public:
	BufferLogger(void);
	virtual ~BufferLogger(void);

public:
	bool Open(string sFileName, bool bWithATime = false);
	void Write(const char* buf, unsigned int size);
	void WriteLine();
	void Write(string str);
	void WirteImmediately(const char* buf, unsigned int size);

private:
	void Flush();

private:
	char buffer_[BUFFER_LOGGER_BUFFER_SIZE];
	int current_;

	string fileName_;
	bool splitFile_;
};
