/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : ReflectionX.cpp
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#include "ReflectionX.h"

std::map<std::string, CreateFuntion> ReflectionClassFactory::m_clsMap;

void* ReflectionClassFactory::GetClassByName(std::string name)
{
	std::map<std::string,CreateFuntion>::const_iterator find;
	find = m_clsMap.find(name);
	if(find==m_clsMap.end())
	{
		return NULL;
	}
	else
	{
		return find->second();
	}
}

bool ReflectionClassFactory::RegistClass(std::string name,CreateFuntion method)
{
	m_clsMap.insert(std::make_pair(name,method));
	return true;
}

