#include "DefaultComponentVisualizer.h"
#include <Runtime/World/Component.h>
#include <Libs/ImGui/imgui.h>
#include <Runtime/Memory/Memory.h>

namespace Portakal
{
	void DefaultComponentVisualizer::OnInitialize()
	{

	}
	void DefaultComponentVisualizer::OnFinalize()
	{

	}
	void DefaultComponentVisualizer::OnPaint()
	{
		ImGui::Text("DEFAULT COMPONENT VISUALIZER");

		Component* pComponent = GetComponent();

		const Array<Field*> fields = pComponent->GetType()->GetFields();
		for (unsigned int i = 0; i < fields.GetCursor(); i++)
		{
			const Field* pField = fields[i];
			if (pField->GetAccessSpecifier() != AccessSpecifier::Public)
				continue;

			const Type* pFieldType = pField->GetFieldType();
			if (pFieldType == typeof(int))
			{
				int value = pField->GetValue<int>(pComponent);
				ImGui::InputInt(*pField->GetFieldName(), &value);
				pField->SetValue<int>(pComponent, value);
			}
			else if (pFieldType == typeof(String))
			{
				char* pBuffer = new char[512];
				String value = pField->GetValue<String>(pComponent);
				Memory::Copy(value.GetSource(), pBuffer, value.GetCursor());
				pBuffer[value.GetCursor()] = '\0';
				ImGui::InputText(*pField->GetFieldName(), pBuffer,512);
				value = pBuffer;
				pField->SetValue<String>(pComponent, value);

				delete[] pBuffer;
			}
		}
	}
}