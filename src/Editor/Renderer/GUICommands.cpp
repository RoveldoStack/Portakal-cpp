#include "GUICommands.h"
#include <Libs/ImGui/imgui.h>
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Memory/Memory.h>

namespace Portakal
{
	int GUICommands::IntField(const String& name, const int value)
	{
		const String title = "##" + name;

		ImGui::Text(*name);
		ImGui::SameLine();

		int mutableValue = value;
		ImGui::InputInt(*title, &mutableValue);

		return mutableValue;
	}
	float GUICommands::FloatField(const String& name, const float value)
	{
		const String title = "##" + name;

		ImGui::Text(*name);
		ImGui::SameLine();

		float mutableValue = value;
		ImGui::InputFloat(*title, &mutableValue);

		return mutableValue;
	}
	long long GUICommands::EnumField(const String& name, const Type* pType, const long long value)
	{
		const String title = "##" + name;
		const Array<String> enumNames = pType->GetEnumNames();
		const Array<long long> enumValues = pType->GetEnumValues();

		int index = enumValues.FindIndex(value);
		const String preview = index == -1 ? "no preview" : enumNames[index];

		ImGui::Text(*name);
		ImGui::SameLine();

		long long valueOut = value;

		if (ImGui::BeginCombo(*title, *preview))
		{
			for (unsigned int i = 0; i < enumNames.GetCursor(); i++)
			{
				const String& enumName = enumNames[i];
				const long long enumValue = enumValues[i];

				if (ImGui::Selectable(*enumName))
				{
					valueOut = enumValue;
				}
			}

			ImGui::EndCombo();
		}

		return valueOut;
	}
	String GUICommands::TextField(const String& name, const String& value)
	{
		const String title = "##" + name;

		ImGui::Text(*name);
		ImGui::SameLine();

		char* buffer = new char[name.GetCursor()*2];
		Memory::Set(buffer, 0, name.GetCursor() * 2);
		Memory::Copy(value.GetSource(), buffer, value.GetCursor());

		ImGui::InputText(*title,buffer,name.GetCursor()*2);

		return buffer;
	}
}