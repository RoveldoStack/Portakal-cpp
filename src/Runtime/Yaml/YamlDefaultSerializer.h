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

		static String ToYaml(const Class* pObject);
		static void ToObject(const String& yamlString, Class* pObject);
	};
}