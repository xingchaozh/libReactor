/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : EventXO.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "Helper.h"

Helper * Helper::instance = 0;

Helper::Helper(void)
{
}

Helper::~Helper(void)
{
	if (0 != instance)
	{
		delete instance;
	}
}

Helper * Helper::Instance()
{
	if (0 == instance)
	{
		instance = new Helper();
	}
	return instance;
}