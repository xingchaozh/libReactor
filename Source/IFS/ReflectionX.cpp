#include "ReflectionX.h"

namespace libReactor
{
	std::map<std::string, ClassCreateCB> ReflectionClassFactory::m_classMap;

	void* ReflectionClassFactory::GetClassByName(std::string className)
	{
		const auto find = m_classMap.find(className);
		if (find == m_classMap.end())
		{
			return NULL;
		}
		else
		{
			return find->second();
		}
	}

	bool ReflectionClassFactory::RegistClass(std::string name, ClassCreateCB method)
	{
		auto result = m_classMap.insert(std::make_pair(name, method));
		return result.second;
	}
}
