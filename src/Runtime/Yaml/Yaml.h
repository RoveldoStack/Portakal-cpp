#pragma once
#include <Runtime/Yaml/IYamlSerializer.h>
#include <Runtime/Yaml/YamlSerializerAttribute.h>
#include <Runtime/Yaml/YamlDefaultSerializer.h>
#include <Libs/Yaml/include/yaml-cpp/yaml.h>

namespace Portakal
{
	/// <summary>
	/// General use yaml class
	/// </summary>
	class PORTAKAL_API Yaml
	{
	public:
		Yaml() = delete;
		~Yaml() = delete;

		/// <summary>
		/// Translates a yaml string into an object
		/// </summary>
		/// <typeparam name="TObject"></typeparam>
		/// <param name="yaml"></param>
		/// <param name="pObject"></param>
		template<typename TObject>
		static void ToObject(const String& yaml, TObject* pObject)
		{
			YamlDefaultSerializer::ToObject(yaml, pObject,typeof(TObject));
		}

		/// <summary>
		/// Translates an object into a yaml string
		/// </summary>
		/// <typeparam name="TObject"></typeparam>
		/// <param name="pObject"></param>
		/// <returns></returns>
		template<typename TObject>
		static String ToYaml(const TObject* pObject)
		{
			return YamlDefaultSerializer::ToYaml(pObject,typeof(TObject));
		}

	};
}