#include "DefaultComponentVisualizer.h"
#include <Runtime/World/Component.h>
#include <Libs/ImGui/imgui.h>
#include <Runtime/Memory/Memory.h>
#include <Runtime/Math/Color4.h>
#include <Editor/GUI/Window/Templates/WorldObserverWindow.h>
#include <Runtime/World/Entity.h>

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

			bool bFieldChanged = false;

			const Type* pFieldType = pField->GetFieldType();
			if (pFieldType == typeof(int))
			{
				int formerValue = pField->GetValue<int>(pComponent);
				int value = formerValue;
				ImGui::InputInt(*pField->GetFieldName(), &value);
				pField->SetValue<int>(pComponent, value);

				bFieldChanged = formerValue != value;
			}
			else if (pFieldType == typeof(float))
			{
				float formerValue = pField->GetValue<float>(pComponent);
				float value = formerValue;
				ImGui::InputFloat(*pField->GetFieldName(), &value);
				pField->SetValue<float>(pComponent, value);

				bFieldChanged = formerValue != value;
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
			else if (pFieldType == typeof(ColorRgbaF))
			{
				ColorRgbaF formerValue = pField->GetValue<ColorRgbaF>(pComponent);
				ColorRgbaF value = formerValue;
				ImGui::ColorPicker4("ClearColor", &value.R);
				pField->SetValue(pComponent, value);

				bFieldChanged = formerValue != value;
			}

			if (bFieldChanged)
			{
				WorldObserverWindow::SignalSceneChanged(pComponent->GetOwnerEntity()->GetOwnerScene());
			}
		}
	}
}