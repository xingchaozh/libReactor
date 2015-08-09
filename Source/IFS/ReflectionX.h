#pragma once

#include <string>  
#include <map>  
#include <iostream>
#include <functional>

#include "../Common/DllCommon.h"

using namespace std;

namespace libReactor
{
	typedef std::function<void* ()> ClassCreateCB;
	typedef std::map<std::string, ClassCreateCB> ClassMap;

	class LIB_REACTOR_API ReflectionClassFactory
	{
	public:
		static void* GetClassByName(std::string name);
		static bool RegistClass(std::string name, ClassCreateCB method);

	private:
		static ClassMap m_classMap;
	};

#define ReflectionRegister(T) \
        (ReflectionClassFactory::RegistClass(typeid(T).name(), [&]()->void *{ return new T; }));
#define AutoReflectionRegister(T) \
	class AutoReflectionRegister##T \
		{ \
	public:\
		AutoReflectionRegister##T() \
			{ \
			ReflectionRegister(T) \
			} \
		}; \
	static const AutoReflectionRegister##T InstanceAutoReflectionRegister##T;
}
