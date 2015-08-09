#pragma once

#include "log.h"

namespace libReactor
{
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

		std::string m_fileName;
		bool splitFile_;
	};
}
