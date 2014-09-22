/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : FaultRaise.h
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/

#ifndef FUAULTMANAGEMENT_H
#define FUAULTMANAGEMENT_H

#include "../Common/Common.h"

#include "../CMS/lockfreequeue.h"

#include <stdarg.h>

#include "..\IOS\BufferLogger.h"

class FaultRaise
{
protected:
    FaultRaise();
    ~FaultRaise();

public:
    bool SetFault(const bool iFaultFlag,const ErrorCode iErrorCode,const string iErrorMessage);
    bool GetLastFault(FaultElement * faultElement);

    int PrintErrors(const char * _format, const va_list _args);
    int PrintErrors(const char * _format...);

    static FaultRaise * Instance();

	void Destroy();
private:
    LockFreeQueue<FaultElement> * faultElementQueue_;
    static FaultRaise * instance;
	BufferLogger logger_;
};

#endif // FUAULTMANAGEMENT_H
