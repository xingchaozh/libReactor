/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : IFS.h
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#ifndef _X_IFS_
#define _X_IFS_

#include "../Common/Common.h"

#include "../CMS/UServerAccepter.h"

#include "../CMS/UDataReader.h"
#include "../CMS/UDataProcesser.h"
#include "../CMS/UServerDataHandler.h"

#include "../CMS/UClientConnector.h"

#include "../CMS/connectkeeper.h"

#include "../CMS/UServerBase.h"

#include "../CMS/UClientBase.h"

#include "../EXPS/FaultRaise.h"

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
		int len = FaultRaise::Instance()->PrintErrors(format,args);
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


#endif//_X_IFS_
