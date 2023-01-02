#pragma once
#include <Runtime/Yaml/YamlSerializer.h>
#include <Runtime/Yaml/YamlSerializerAttribute.h>
#include <Libs/Yaml/include/yaml-cpp/yaml.h>

namespace Portakal
{
	class PORTAKAL_API Yaml
	{
	public:
		Yaml() = delete;
		~Yaml() = delete;

		template<typename TObject>
		static void ToObject(const String& yaml, TObject* pObject)
		{
			/*
			* Get serializer
			*/
			YamlSerializer* pSerializer = GetSerializer<TObject>();

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

		template<typename TObject>
		static String ToYaml(const TObject* pObject)
		{
			/*
			* Get serializer
			*/
			YamlSerializer* pSerializer = GetSerializer<TObject>();

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
		template<typename TObject>
		static YamlSerializer* GetSerializer()
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
					return (YamlSerializer*)pType->CreateDefaultHeapObject();
			}

			return nullptr;
		}
	};
}