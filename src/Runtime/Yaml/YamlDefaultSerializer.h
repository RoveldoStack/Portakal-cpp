#pragma once
#include <Runtime/Yaml/Yaml.h>
#include <Runtime/Reflection/Class.h>

namespace Portakal
{
	/// <summary>
	/// It's a default yaml serializer unit for objects and fields
	/// </summary>
	class PORTAKAL_API YamlDefaultSerializer final
	{
	public:
		static String ObjectToYaml(const Class* pObject);
		static void YamlToObject(Class* pObject,const String& yaml);
		static String FieldToYaml(const Class* pObject, const Field* pField);
		static void SetField(const Class* pObject, const Field* pField, const String& yamlString);
	public:
		YamlDefaultSerializer() = delete;
		~YamlDefaultSerializer() = delete;

	};
}