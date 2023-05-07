#pragma once
#include <Runtime/Reflection/Class.h>
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class PORTAKAL_API YamlDefaultSerializer
	{
	public:
		YamlDefaultSerializer() = delete;
		~YamlDefaultSerializer() = delete;

		static String ToYaml(const void* pObject,const Type* pType);
		static void ToObject(const String& yamlString, void* pObject,const Type* pType);
	};
}