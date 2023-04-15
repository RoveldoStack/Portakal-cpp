#include "YamlDefaultSerializer.h"
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Memory/Memory.h>

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
				else if (pFieldType == typeof(ColorRgbaF))
				{
					const ColorRgbaF value = pField->GetValue<ColorRgbaF>((void*)pObject);

					char buffer[sizeof(ColorRgbaF)];
					Memory::Set(buffer, 0, sizeof(buffer));
					Memory::Copy(&value, buffer, sizeof(buffer));

					emitter << YAML::Value << buffer;
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
	void EmitField(YAML::Emitter& emitter, const Class* pObject, const Field* pField,const bool bRoot)
	{
		const Type* pFieldType = pField->GetFieldType();
		const bool bSimpleField = pFieldType->IsEnum() || pFieldType->GetFields().GetCursor() == 0;

		if (bSimpleField && !bRoot)
			emitter << YAML::Key << *pField->GetFieldName();

		emitter << YAML::BeginMap;

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
			else if (pFieldType == typeof(ColorRgbaF))
			{
				const ColorRgbaF value = pField->GetValue<ColorRgbaF>((void*)pObject);

				char buffer[sizeof(ColorRgbaF)];
				Memory::Set(buffer, 0, sizeof(buffer));
				Memory::Copy(&value, buffer, sizeof(buffer));

				emitter << YAML::Value << buffer;
			}
			else // other custom object
			{
				const Array<Field*> fields = pFieldType->GetFields();

				Class* pOther = pField->GetAddress<Class>((void*)pObject);

				for (unsigned int i = 0; i < fields.GetCursor(); i++)
				{
					EmitField(emitter, pOther, fields[i],false);
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

	void YamlDefaultSerializer::YamlToObject(Class* pObject, const String& yaml)
	{
		YAML::Node node = YAML::Load(*yaml);
	}

	String YamlDefaultSerializer::FieldToYaml(const Class* pObject, const Field* pField)
	{
		const Type* pFieldType = pField->GetFieldType();

		YAML::Emitter emitter;

		EmitField(emitter, pObject, pField,true);

		return emitter.c_str();
	}

	void ConstructNestedField(const Class* pObject, const Field* pField, YAML::Node& node)
	{
		const Type* pFieldType = pField->GetFieldType();
		const Array<Field*> fields = pFieldType->GetFields();

		for (unsigned int i = 0; i < fields.GetCursor(); i++)
		{
			const Field* pSubField = fields[i];
			const Type* pSubFieldType = pSubField->GetFieldType();

			YAML::Node subFieldNode = node[*pSubField->GetFieldName()];

			if (subFieldNode.IsNull()) // its invalid
				continue;

			if (pSubFieldType->IsEnum())
			{
				const long long value = String::ToLongLong(subFieldNode.as<std::string>().c_str());
				pSubField->SetValue<long long>((void*)pObject, value);
			}
			else
			{
				if (pSubFieldType == typeof(int))
				{
					const int value = String::ToInteger(subFieldNode.as<std::string>().c_str());
					pSubField->SetValue<int>((void*)pObject, value);
				}
				else if (pSubFieldType == typeof(float))
				{
					const float value = String::ToFloat(subFieldNode.as<std::string>().c_str());
					pSubField->SetValue<float>((void*)pObject, value);
				}
				else if (pSubFieldType == typeof(String))
				{
					const String value = subFieldNode.as<std::string>().c_str();
					pSubField->SetValue<String>((void*)pObject, value);
				}
				else if (pFieldType == typeof(ColorRgbaF))
				{
					char buffer[sizeof(ColorRgbaF)];
					const String content = node.as<std::string>().c_str();
					const ColorRgbaF value = *((ColorRgbaF*)(*content));

					pField->SetValue<ColorRgbaF>((void*)pObject, value);
				}
				else // create nested
				{
					/*
					* Validate if nested
					*/
					const bool bNested = pSubFieldType->GetFields().GetCursor() > 0;
					if (bNested)
						ConstructNestedField(pSubField->GetAddress<Class>((void*)pObject), pSubField, subFieldNode);
				}
			}

		}
	}
	void ConstructSimpleField(const Class* pObject, const Field* pField,YAML::Node& node)
	{
		const Type* pFieldType = pField->GetFieldType();

		if (pFieldType->IsEnum())
		{
			const long long value = String::ToLongLong(node.as<std::string>().c_str());
			pField->SetValue<long long>((void*)pObject, value);
		}
		else
		{
			if (pFieldType->IsSubClassOf(typeof(ResourceSubObject)))
			{
				const Guid value = Guid::FromString(node.as<std::string>().c_str());
				pField->SetValue<Guid>((void*)pObject, value);
			}
			else if (pFieldType == typeof(float))
			{
				const float value = String::ToFloat(node.as<std::string>().c_str());
				pField->SetValue<int>((void*)pObject, value);
			}
			else if (pFieldType == typeof(int))
			{
				const int value = String::ToInteger(node.as<std::string>().c_str());
				pField->SetValue<int>((void*)pObject, value);
			}
			else if (pFieldType == typeof(ColorRgbaF))
			{
				char buffer[sizeof(ColorRgbaF)];
				const String content = node.as<std::string>().c_str();
				const ColorRgbaF value = *((ColorRgbaF*)(*content));

				pField->SetValue<ColorRgbaF>((void*)pObject, value);
			}
			else // custom class
			{
				if (pFieldType->GetFields().GetCursor() > 0)
				{
					ConstructNestedField(pField->GetAddress<Class>((void*)pObject), pField, node);
				}
			}
			
		}
	}
	void YamlDefaultSerializer::SetField(const Class* pObject, const Field* pField, const String& yamlString)
	{
		YAML::Node node = YAML::Load(*yamlString);
		const bool bSimpleField = pField->GetFieldType()->IsEnum() || pField->GetFieldType()->GetFields().GetCursor() == 0;

		if (bSimpleField)
			ConstructSimpleField(pObject, pField, node);
		else
			ConstructNestedField(pField->GetAddress<Class>((void*)pObject), pField, node);
	}
}