#pragma once
#include <Runtime/Yaml/IYamlSerializer.h>
#include <Runtime/Yaml/YamlSerializerAttribute.h>
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
			/*
			* Get serializer
			*/
			IYamlSerializer* pSerializer = GetSerializer<TObject>();

			/*
			* Validate serializer
			*/
			if (pSerializer == nullptr)
				return;

			/*
			* Get yaml node
			*/
			YAML::Node node = YAML::Load(*yaml);

			/*
			* Run deserialization
			*/
			pSerializer->Deserialize(node, pObject);

			delete pSerializer;
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
			/*
			* Get serializer
			*/
			IYamlSerializer* pSerializer = GetSerializer<TObject>();

			/*
			* Validate serializer
			*/
			if (pSerializer == nullptr)
				return "";

			/*
			* Create emitter
			*/
			YAML::Emitter emitter;

			/*
			* Run serialization
			*/
			pSerializer->Serialize(emitter, (const Class*)pObject);

			return emitter.c_str();
		}

		/// <summary>
		/// Returns the serializer of the given template type
		/// </summary>
		/// <typeparam name="TObject"></typeparam>
		/// <returns></returns>
		template<typename TObject>
		static IYamlSerializer* GetSerializer()
		{
			Type* pTargetType = TypeAccessor<TObject>::GetAccessorType();

			const Array<Type*> types = Assembly::GetProcessAssembly()->GetTypes();


			for (unsigned int i = 0; i < types.GetCursor(); i++)
			{
				Type* pType = types[i];

				const YamlSerializerAttribute* pAttribute = pType->GetAttribute<YamlSerializerAttribute>();

				if (pAttribute == nullptr)
					continue;

				if (pAttribute->GetTargetSerializerType() == pTargetType)
					return (IYamlSerializer*)pType->CreateDefaultHeapObject();
			}

			return nullptr;
		}
	};
}