/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : DataSource.h
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "../Common/Common.h"

class DataSource
{
public:
    DataSource();
public:
    virtual bool RetrieveData(void * data) = 0;
};

#endif // DATASOURCE_H
