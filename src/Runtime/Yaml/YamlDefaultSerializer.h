#pragma once
#include <Runtime/Yaml/Yaml.h>
#include <Runtime/Reflection/Class.h>

namespace Portakal
{
	class PORTAKAL_API YamlDefaultSerializer final
	{
	public:
		static String ObjectToYaml(const Class* pObject);
	public:
		YamlDefaultSerializer() = delete;
		~YamlDefaultSerializer() = delete;

	};
}