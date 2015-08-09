#pragma once

#include "../Common/Common.h"

#include "../CMS/UServerDataHandler.h"

#include "../CMS/ConnectKeeper.h"

#include "../CMS/TelegramPackager.h"

#include "../CMS/UBufferContainer.h"

#include "../CMS/UServerBase.h"

#include "../CMS/UClientBase.h"

#include "../CMS/UClientDataHandler.h"

#include "../EXPS/FaultRaise.h"

#include "../OSIS/SocketX.h"

#include "../OSIS/SocketHelper.h"

#include "../OSIS/Thread.h"

extern unsigned int GetCurrentThreadId_X();

class IFS
{
public:
	IFS()
	{

	}

public:
	static int PrintErrors(const char * format, ...)
	{
#if DEBUG_X
		va_list args;
		va_start( args, format );
		int len = libReactor::FaultRaise::Instance()->PrintErrors(format,args);
		va_end( args );
		return len;
#else
		va_list args;
		va_start( args, format );
		char buffer[FAULT_BUFFER_LEN];
		int len = vprintf(format,args);
		int cnt = vsprintf(buffer, format,args);
		va_end( args );
		return len;
#endif
	}
};
