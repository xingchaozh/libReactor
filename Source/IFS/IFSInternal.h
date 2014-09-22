/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : IFSInternal.h
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#ifndef _X_IFS_INTERNAL_
#define _X_IFS_INTERNAL_

#include "../Common/Common.h"
#include "../OSIS/ThreadX.h"
#include "../OSIS/TcpSocketXO.h"
#include "../OSIS/UdpSocketXO.h"
#include "../OSIS/EventXO.h"
#include "../OSIS/MutexXO.h"


//class IFS
//{
//public:
//	IFS()
//	{
//
//	}
//
//public:
//	static int PrintErrors(const char * format, ...)
//	{
//#if DEBUG_X
//		va_list args;
//		va_start( args, format );
//		//int len = FaultManagement::Instance()->PrintErrors(format,args);
//		va_end( args );
//		return len;
//#else
//		va_list args;
//		va_start( args, format );
//		char buffer[FAULT_BUFFER_LEN];
//		int len = vprintf(format,args);
//		int cnt = vsprintf(buffer, format,args);
//		va_end( args );
//		return len;
//#endif
//	}
//};


#endif//_X_IFS_INTERNAL_