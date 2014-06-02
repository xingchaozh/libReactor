/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : LogUseBuffer.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "LogUseBuffer.h"

LogUseBuffer::LogUseBuffer(void):current_(0),autoSplitFile_(true)
{
	memset(buffer_,0,sizeof(char)*LOG_BUFFER_SIZE);
	logEnabled_ = true;
}

LogUseBuffer::~LogUseBuffer(void)
{
	Flush();
	Close();
}

bool LogUseBuffer::Open(string sFileName, bool bWithATime)
{
	fileName_ = sFileName;
	if (bWithATime)
	{
		sFileName = fileName_ + GetCurTimeStr();
	}
	srand((unsigned int)time(0));
	sFileName = sFileName + " "+ ValueToStr(rand()) + ".log";

	fopen_s(&logFile_,sFileName.c_str(), "w");
	/* set up input stream for minimal disk access, using our own character buffer */ 
	//Consider that the function is not existed.
	//if (setvbuf ( m_logFile, m_buffer, _IOFBF, BUFFER_SIZE )!= 0)
	//{
	//	printf("failed to set up buffer for input file\n");
	//}
	//else
	//{
	//	printf("buffer set up for input file\n");
	//}
	
	if( !logFile_ )
	{
		return false;
	}
	return true;
}

void LogUseBuffer::Write(const char* buf, unsigned int size)
{
	if (logEnabled_)
	{
		if (size > LOG_BUFFER_SIZE)
		{
			this->Flush();
			WirteImmediately(buf,size);
			return;
		}

		if (current_ + size > LOG_BUFFER_SIZE)
		{
			this->Flush();
		}

		memcpy(buffer_+current_, buf, size);
		current_ += size;
	}
}

void LogUseBuffer::WriteLn()
{
	string strln="\n";
	Write(strln.c_str(),strln.size());
}

void LogUseBuffer::Write(string str)
{
	Write(str.c_str(),str.size());
}

void LogUseBuffer::WirteImmediately(const char* buf, unsigned int size)
{
	fwrite(buf,sizeof(char),size,logFile_);

	if (autoSplitFile_)
	{
		if (Size() > MAX_SINGLE_LOG_FILE_SIZE)
		{
			Close();
			Open(fileName_,true);
		}
	}
}

void LogUseBuffer::Flush()
{
	buffer_[current_]='\0';
	WirteImmediately(buffer_,current_);
	current_ = 0;
}
