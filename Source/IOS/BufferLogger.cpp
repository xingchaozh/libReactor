#include "BufferLogger.h"

namespace libReactor
{
	BufferLogger::BufferLogger(void) :current_(0), splitFile_(true)
	{
		memset(buffer_, 0, sizeof(char)*BUFFER_LOGGER_BUFFER_SIZE);
		enabled_ = true;
		m_fileName = "";
	}

	BufferLogger::~BufferLogger(void)
	{
		Flush();
		Close();
	}

	bool BufferLogger::Open(string sFileName, bool bWithATime)
	{
		m_fileName = sFileName;
		if (bWithATime)
		{
			sFileName = m_fileName + GetCurTimeStr();
		}
		srand((unsigned int)time(0));
		sFileName = "log\\" + sFileName + " " + ValueToStr(rand()) + ".log";
		fopen_s(&outputFile_, sFileName.c_str(), "w");

		if (!outputFile_)
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
				WirteImmediately(buf, size);
				return;
			}

			if (current_ + size > BUFFER_LOGGER_BUFFER_SIZE)
			{
				this->Flush();
			}

			memcpy(buffer_ + current_, buf, size);
			current_ += size;
		}
	}

	void BufferLogger::WriteLine()
	{
		string strln = "\n";
		Write(strln.c_str(), strln.size());
	}

	void BufferLogger::Write(string str)
	{
		Write(str.c_str(), str.size());
	}

	void BufferLogger::WirteImmediately(const char* buf, unsigned int size)
	{
		if (!outputFile_)
		{
			return;
		}

		fwrite(buf, sizeof(char), size, outputFile_);

		if (splitFile_)
		{
			if (Size() > MAX_SINGLE_LOG_FILE_SIZE)
			{
				Close();
				Open(m_fileName, true);
			}
		}
	}

	void BufferLogger::Flush()
	{
		buffer_[current_] = '\0';
		WirteImmediately(buffer_, current_);
		current_ = 0;
	}
}
