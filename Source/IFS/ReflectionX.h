/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : ReflectionX.h
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#pragma once

#include <string>  
#include <map>  
#include <iostream>

using namespace std;
typedef void* (*CreateFuntion)(void);

class ReflectionClassFactory
{
public:
	static void* GetClassByName(std::string name);
	static bool RegistClass(std::string name,CreateFuntion method);

private:
	static std::map<std::string,CreateFuntion> m_clsMap;
};


class ReflectionRegistyClass
{
public:
	ReflectionRegistyClass(std::string name, CreateFuntion method);
};

template<class T>
class ReflectionRegister
{

public:
	ReflectionRegister()
	{
	}

	static bool Register()
	{
		return ReflectionClassFactory::RegistClass(typeid(T).name(), ReflectionRegister<T>::CreateInstance);
	}

	static void * CreateInstance()
	{
		return new T;
	}
};


