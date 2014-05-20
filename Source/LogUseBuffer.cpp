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

LogUseBuffer::LogUseBuffer(void):m_current(0),m_bAtuoSplitFile(true)
{
	memset(m_buffer,0,sizeof(char)*BUFFER_SIZE);
	m_bLogEnabled = true;
}

LogUseBuffer::~LogUseBuffer(void)
{
	Flush();
	Close();
}

bool LogUseBuffer::Open(string sFileName, bool bWithATime)
{
	m_sFileName = sFileName;
	if (bWithATime)
	{
		sFileName = m_sFileName + GetCurTimeStr();
	}
	srand((unsigned int)time(0));
	sFileName = sFileName + " "+ ValueToStr(rand()) + ".log";

	fopen_s(&m_logFile,sFileName.c_str(), "w");
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
	
	if( !m_logFile )
	{
		return false;
	}
	return true;
}

void LogUseBuffer::Write(const char* buf, unsigned int size)
{
	if (m_bLogEnabled)
	{
		if (size > BUFFER_SIZE)
		{
			this->Flush();
			WirteImmediately(buf,size);
			return;
		}

		if (m_current + size > BUFFER_SIZE)
		{
			this->Flush();
		}

		memcpy(m_buffer+m_current, buf, size);
		m_current += size;
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
	fwrite(buf,sizeof(char),size,m_logFile);

	if (m_bAtuoSplitFile)
	{
		if (Size() > MAX_SINGLE_LOG_FILE_SIZE)
		{
			Close();
			Open(m_sFileName,true);
		}
	}
}

void LogUseBuffer::Flush()
{
	m_buffer[m_current]='\0';
	WirteImmediately(m_buffer,m_current);
	m_current = 0;
}
