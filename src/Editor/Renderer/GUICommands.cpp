#include "GUICommands.h"
#include <Libs/ImGui/imgui.h>
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Memory/Memory.h>
#include <Runtime/Log/Log.h>
#include <Libs/ImGui/misc/cpp/imgui_stdlib.h>

namespace Portakal
{
	void GUICommands::Text(const String& content)
	{
		ImGui::Text(*content);
	}
	int GUICommands::IntField(const String& name, const int value)
	{
		const String title = "##" + name;

		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		ImGui::Text(*name);
		ImGui::PopStyleColor();

		ImGui::SameLine();

		int mutableValue = value;
		ImGui::InputInt(*title, &mutableValue);

		return mutableValue;
	}
	int GUICommands::IntField(const String& name, const int value, bool& bChanged)
	{
		const String title = "##" + name;

		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		ImGui::Text(*name);
		ImGui::PopStyleColor();

		ImGui::SameLine();

		int mutableValue = value;
		ImGui::InputInt(*title, &mutableValue);

		bChanged = value != mutableValue;

		return mutableValue;
	}
	float GUICommands::FloatField(const String& name, const float value)
	{
		const String title = "##" + name;

		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		ImGui::Text(*name);
		ImGui::PopStyleColor();

		ImGui::SameLine();

		float mutableValue = value;
		ImGui::InputFloat(*title, &mutableValue);


		return mutableValue;
	}
	float GUICommands::FloatField(const String& name, const float value, bool& bChanged)
	{
		const String title = "##" + name;

		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		ImGui::Text(*name);
		ImGui::PopStyleColor();

		ImGui::SameLine();

		float mutableValue = value;
		ImGui::InputFloat(*title, &mutableValue);

		bChanged = value != mutableValue;

		return mutableValue;
	}
	long long GUICommands::EnumField(const String& name, const Type* pType, const long long value)
	{
		const String title = "##" + name;
		const Array<String> enumNames = pType->GetEnumNames();
		const Array<long long> enumValues = pType->GetEnumValues();

		int index = enumValues.FindIndex(value);
		const String preview = index == -1 ? "no preview" : enumNames[index];

		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		ImGui::Text(*name);
		ImGui::PopStyleColor();

		ImGui::SameLine();

		long long valueOut = value;

		//ImGui::SetNextItemWidth(ImGui::CalcTextSize(*preview).x*2);
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
	long long GUICommands::EnumField(const String& name, const Type* pType, const long long value, bool& bChanged)
	{
		const String title = "##" + name;
		const Array<String> enumNames = pType->GetEnumNames();
		const Array<long long> enumValues = pType->GetEnumValues();

		int index = enumValues.FindIndex(value);
		const String preview = index == -1 ? "no preview" : enumNames[index];


		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		ImGui::Text(*name);
		ImGui::PopStyleColor();
		ImGui::SameLine();

		long long valueOut = value;
		//ImGui::SetNextItemWidth(ImGui::CalcTextSize(*preview).x*2);
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

		bChanged = value != valueOut;

		return valueOut;
	}
	Vector2F GUICommands::Vector2FField(const String& name, const Vector2F value)
	{
		const String title = "##" + name;

		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		ImGui::Text(*name);
		ImGui::PopStyleColor();

		Vector2F mutableValue = value;
		ImGui::InputFloat2(*title, &mutableValue.X);

		return mutableValue;
	}
	Vector2F GUICommands::Vector2FField(const String& name, const Vector2F value, bool& bChanged)
	{
		const String title = "##" + name;

		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		ImGui::Text(*name);
		ImGui::PopStyleColor();

		Vector2F mutableValue = value;
		ImGui::InputFloat2(*title, &mutableValue.X);

		bChanged = mutableValue != value;

		return mutableValue;
	}
	Vector3F GUICommands::Vector3FField(const String& name, const Vector3F value)
	{
		const String title = "##" + name;

		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		ImGui::Text(*name);
		ImGui::PopStyleColor();

		Vector3F mutableValue = value;
		ImGui::InputFloat3(*title, &mutableValue.X);

		return mutableValue;
	}
	Vector3F GUICommands::Vector3FField(const String& name, const Vector3F value, bool& bChanged)
	{
		const String title = "##" + name;

		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		ImGui::Text(*name);
		ImGui::PopStyleColor();

		Vector3F mutableValue = value;
		ImGui::InputFloat3(*title, &mutableValue.X);

		bChanged = mutableValue != value;

		return mutableValue;
	}
	String GUICommands::TextField(const String& name, const String& value)
	{
		const String title = "##" + name;

		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		ImGui::Text(*name);
		ImGui::PopStyleColor();
		ImGui::SameLine();

		std::string str = *value == nullptr ? "" : *value;

		ImGui::InputText(*title, &str, ImGuiInputTextFlags_None);

		const String valueOut = str.c_str();

		return valueOut;
	}
	String GUICommands::TextField(const String& name, const String& value, bool& bChanged)
	{
		const String title = "##" + name;

		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		ImGui::Text(*name);
		ImGui::PopStyleColor();
		ImGui::SameLine();

		std::string str = *value == nullptr ? "" : *value;

		ImGui::InputText(*title, &str, ImGuiInputTextFlags_None);

		const String valueOut = str.c_str();

		bChanged = valueOut != value;

		return valueOut;
	}

	String GUICommands::MultilineTextField(const String& name, const String& value, const Vector2F& size,const GUIInputTextFlags flags)
	{
		const String title = "##" + name;

		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		ImGui::Text(*name);
		ImGui::PopStyleColor();

		std::string str = *value == nullptr ? "" : *value;
		ImGui::InputTextMultiline(*title, &str, { size.X,size.Y }, (ImGuiInputTextFlags)flags);

		const String valueOut = str.c_str();

		return valueOut;
	}

	
	ColorRgbaF GUICommands::RgbaFField(const String& name, const ColorRgbaF& value)
	{
		const String title = "##" + name;


		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		ImGui::Text(*name);
		ImGui::PopStyleColor();
		ImGui::SameLine();

		ColorRgbaF mutableValue = value;
		ImGui::ColorEdit4(*title, &mutableValue.R);

		return mutableValue;
	}
	ColorRgbaF GUICommands::RgbaFField(const String& name, const ColorRgbaF& value, bool& bChanged)
	{
		const String title = "##" + name;

		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_Text]);
		ImGui::Text(*name);
		ImGui::PopStyleColor();

		ImGui::SameLine();

		ColorRgbaF mutableValue = value;
		ImGui::ColorEdit4(*title, &mutableValue.R);

		bChanged = mutableValue != value;
		return mutableValue;
	}
	void GUICommands::PushColor(const GUIColorType type, const ColorRgbaF& color)
	{
		ImGui::PushStyleColor((ImGuiCol)type, ImGui::ColorConvertFloat4ToU32({ color.R,color.G,color.B,color.A }));
	}
	void GUICommands::PopColor()
	{
		ImGui::PopStyleColor();
	}

}