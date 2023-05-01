#include "GUIDefaultVisualizer.h"
#include <Libs/ImGui/imgui.h>
#include <Libs/ImGui/misc/cpp/imgui_stdlib.h>
#include <Editor/Renderer/GUICommands.h>
#include <string>

namespace Portakal
{
	void DrawObject(void* pObject, const Type* pType);

	void DrawPrimitive(void* pObject, const Type* pType)
	{
		const String label = "##" + String::GetFromLongLong((long long)pObject);

		switch (pType->GetTypeCode())
		{
			case Portakal::TypeCodes::Composed:
				break;
			case Portakal::TypeCodes::String:
			{
				String* value = (String*)pObject;

				/*
				* ImGui std string conversion
				*/
				std::string str = value->GetSource() == nullptr ? "" : **value;
				ImGui::InputText(*label, &str, ImGuiInputTextFlags_None);
				const String newValue = str.c_str();
				*(String*)pObject = newValue;

				break;
			}
			case Portakal::TypeCodes::Char:
			{
				break;
			}
			case Portakal::TypeCodes::UChar:
				break;
			case Portakal::TypeCodes::Int:
			{
				int* pValue = (int*)pObject;
				ImGui::InputInt(*label, pValue);
				break;
			}
			case Portakal::TypeCodes::UInt:
				break;
			case Portakal::TypeCodes::Short:
				break;
			case Portakal::TypeCodes::UShort:
				break;
			case Portakal::TypeCodes::Float:
			{
				float* pValue = (float*)pObject;
				ImGui::InputFloat(*label, pValue);
				break;
			}
			case Portakal::TypeCodes::Double:
				break;
			case Portakal::TypeCodes::Long:
				break;
			case Portakal::TypeCodes::LongLong:
				break;
			case Portakal::TypeCodes::ULong:
				break;
			case Portakal::TypeCodes::ULongLong:
				break;
			default:
				break;
		}
	}

	String GetEnumPreview(const Array<String>& names,const Array<long long>& values,const long long value)
	{
		for (unsigned int i = 0; i < values.GetCursor(); i++)
		{
			if (values[i] == value)
			{
				return names[i];
			}
		}

		return names[0];
	}

	void DrawEnum(void* pObject, const Type* pType, const Field* pField)
	{
		const String label = "##" + pField->GetFieldName() + String::GetFromInteger(*(int*)pObject);

		long long* pValue = (long long*)pObject;

		const Array<String> enumNames = pType->GetEnumNames();
		const Array<long long> enumValues = pType->GetEnumValues();
		const String preview = GetEnumPreview(enumNames,enumValues,*pValue);
		if (ImGui::BeginCombo(*label,*preview))
		{
			for (unsigned int i = 0; i < enumNames.GetCursor(); i++)
			{
				const String name = enumNames[i];
				const long long value = enumValues[i];

				if (ImGui::Selectable(*name))
				{
					*pValue = value;
				}
			}

			ImGui::EndCombo();
		}
		
	}

	void DrawArray(void* pObject, const Type* pElementType, const Field* pField)
	{
		const String label = pField->GetFieldName()+ "##" + String::GetFromInteger(*(int*)pObject);

		Array<char>* pArray = (Array<char>*)pObject;
		const unsigned int count = pArray->GetCursor();
		const Type* pFieldType = pField->GetFieldType();


		if (ImGui::TreeNode(*label))
		{
			if (count == 0)
				ImGui::Text("No elements in array");
			else
				ImGui::Text(*String::GetFromInteger(pArray->GetCursor()));

			for (unsigned int i = 0; i < pArray->GetCursor(); i++)
			{
				void* pLocation = (Byte*)pArray->GetData() + i * pElementType->GetSize();

				if (pElementType->IsPrimitive())
				{
					DrawPrimitive(pLocation,pElementType);
					continue;
				}

				if (pElementType->IsEnum())
				{
					ImGui::Text(*pField->GetFieldName());
					ImGui::SameLine();
					DrawEnum(pLocation, pFieldType, pField);
					continue;
				}

				if (pElementType->IsArray())
				{
					DrawArray(pLocation, pField->GetArrayElementType(), pField);
					continue;
				}

				const String elementLabel = pElementType->GetTypeName() + "##" + String::GetFromLongLong((long long)pLocation);
				if (ImGui::TreeNode(*elementLabel))
				{
					DrawObject(pLocation, pElementType);
					ImGui::TreePop();
				}
			}

			if (ImGui::Button("+"))
			{
				pArray->AddIndirect();
			}

			ImGui::TreePop();
		}
	}

	void DrawObject(void* pObject,const Type* pType)
	{
		const Array<Field*> fields = pType->GetFields();
		for (unsigned int i = 0; i < fields.GetCursor(); i++)
		{
			const Field* pField = fields[i];
			const Type* pFieldType = pField->GetFieldType();
			void* pLocation = (Byte*)pObject + pField->GetOffset();

			/*
			* Check if primitive
			*/
			if (pFieldType->IsPrimitive())
			{
				ImGui::Text(*pField->GetFieldName());
				ImGui::SameLine();

				DrawPrimitive(pLocation, pFieldType);
				continue;
			}

			/*
			* Check if enum
			*/
			if (pFieldType->IsEnum())
			{
				ImGui::Text(*pField->GetFieldName());
				ImGui::SameLine();
				DrawEnum(pLocation, pFieldType,pField);
				continue;
			}

			/*
			* Check if array
			*/
			if (pFieldType->IsArray())
			{
				DrawArray(pLocation, pField->GetArrayElementType(), pField);
				continue;
			}

			/*
			* Then it's a composed type
			*/
			if (ImGui::TreeNode(*pFieldType->GetTypeName()))
			{
				DrawObject(pLocation, pFieldType);
				ImGui::TreePop();
			}
		}
	}
	void GUIDefaultVisualizer::DrawDefaultObject(Class* pObject)
	{
		/*
		* Validate object
		*/
		if (pObject == nullptr)
			return;

		/*
		* Get and valide object type
		*/
		const Type* pType = pObject->GetType();
		if (pType == nullptr)
			return;

		/*
		* Draw object
		*/
		DrawObject(pObject, pType);
	}
}