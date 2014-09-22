/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : DataHandler.h
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "../Common/Common.h"

class DataHandler
{
public:
    DataHandler();
public:
    virtual void DataHanle(UdpBuffer & udpBuffer) = 0;
};

#endif // DATAHANDLER_H
