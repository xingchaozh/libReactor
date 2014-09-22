/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : BufferLogger.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "BufferLogger.h"

BufferLogger::BufferLogger(void):current_(0),splitFile_(true)
{
	memset(buffer_,0,sizeof(char)*BUFFER_LOGGER_BUFFER_SIZE);
	enabled_ = true;
}

BufferLogger::~BufferLogger(void)
{
	Flush();
	Close();
}

bool BufferLogger::Open(string sFileName, bool bWithATime)
{
	fileName_ = sFileName;
	if (bWithATime)
	{
		sFileName = fileName_ + GetCurTimeStr();
	}
	srand((unsigned int)time(0));
	sFileName = sFileName + " "+ ValueToStr(rand()) + ".log";

	fopen_s(&outputFile_,sFileName.c_str(), "w");

	if( !outputFile_ )
	{
		return false;
	}
	return true;
}

void BufferLogger::Write(const char* buf, unsigned int size)
{
	if (enabled_)
	{
		if (size > BUFFER_LOGGER_BUFFER_SIZE)
		{
			this->Flush();
			WirteImmediately(buf,size);
			return;
		}

		if (current_ + size > BUFFER_LOGGER_BUFFER_SIZE)
		{
			this->Flush();
		}

		memcpy(buffer_+current_, buf, size);
		current_ += size;
	}
}

void BufferLogger::WriteLine()
{
	string strln="\n";
	Write(strln.c_str(),strln.size());
}

void BufferLogger::Write(string str)
{
	Write(str.c_str(),str.size());
}

void BufferLogger::WirteImmediately(const char* buf, unsigned int size)
{
	fwrite(buf,sizeof(char),size,outputFile_);

	if (splitFile_)
	{
		if (Size() > MAX_SINGLE_LOG_FILE_SIZE)
		{
			Close();
			Open(fileName_,true);
		}
	}
}

void BufferLogger::Flush()
{
	buffer_[current_]='\0';
	WirteImmediately(buffer_,current_);
	current_ = 0;
}
