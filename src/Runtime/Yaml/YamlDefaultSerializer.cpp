#include "YamlDefaultSerializer.h"
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	void EmitObject(YAML::Emitter& emitter, const Class* pObject)
	{
		const Type* pType = pObject->GetType();
		const Array<Field*> fields = pType->GetFields();

		emitter << YAML::BeginMap;

		for (unsigned int i = 0; i < fields.GetCursor(); i++)
		{
			const Field* pField = fields[i];
			const Type* pFieldType = pField->GetFieldType();

			emitter << YAML::Key << *pField->GetFieldName();

			if (pFieldType->IsEnum())
			{
				const long long value = pField->GetValue<long long>((void*)pObject);
				emitter << YAML::Value << value;
			}
			else
			{
				if (pFieldType == typeof(int))
				{
					const int value = pField->GetValue<int>((void*)pObject);
					emitter << YAML::Value << *String::GetFromInteger(value);
				}
				else if (pFieldType == typeof(float))
				{
					const float value = pField->GetValue<float>((void*)pObject);
					emitter << YAML::Value << *String::GetFromFloat(value);
				}
				else if (pFieldType == typeof(String))
				{
					const String value = pField->GetValue<String>((void*)pObject);
					emitter << YAML::Value << *value;
				}
				else // other custom object
				{
					Class* pOther = pField->GetAddress<Class>((void*)pObject);
					EmitObject(emitter, pOther);
				}
			}
		}

		emitter << YAML::EndMap;
	}
	String YamlDefaultSerializer::ObjectToYaml(const Class* pObject)
	{
		const Type* pType = pObject->GetType();
		
		YAML::Emitter emitter;

		emitter << YAML::BeginDoc;

		EmitObject(emitter, pObject);

		emitter << YAML::EndDoc;

		return emitter.c_str();
	}
}