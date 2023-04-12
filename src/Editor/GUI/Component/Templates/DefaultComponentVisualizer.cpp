#include "DefaultComponentVisualizer.h"
#include <Runtime/World/Component.h>
#include <Libs/ImGui/imgui.h>
#include <Runtime/Memory/Memory.h>
#include <Runtime/Math/Color4.h>
#include <Editor/GUI/Window/Templates/WorldObserverWindow.h>
#include <Runtime/World/Entity.h>
#include <Editor/Renderer/GUICommands.h>

namespace Portakal
{
	void DefaultComponentVisualizer::OnInitialize()
	{

	}
	void DefaultComponentVisualizer::OnFinalize()
	{

	}

	void DrawField(Class* pObject,const Field* pField)
	{
		const Type* pFieldType = pField->GetFieldType();


		if (pFieldType->IsEnum())
		{
			const long long value = pField->GetValue<long long>(pObject);
			pField->SetValue<long long>(pObject, GUICommands::EnumField(pField->GetFieldName(), pField->GetFieldType(), value));
		}
		else
		{
			if (pFieldType == typeof(int))
			{
				const int value = pField->GetValue<int>(pObject);
				pField->SetValue<int>(pObject, GUICommands::IntField(pField->GetFieldName(), value));
			}
			else if (pFieldType == typeof(float))
			{
				const float value = pField->GetValue<float>(pObject);
				pField->SetValue<float>(pObject, GUICommands::FloatField(pField->GetFieldName(), value));
			}
			else if (pFieldType == typeof(String))
			{
				const String value = pField->GetValue<String>(pObject);
				pField->SetValue<String>(pObject, GUICommands::TextField(pField->GetFieldName(), value));
			}
			else // custom class
			{
				const Array<Field*> fields = pFieldType->GetFields();
				Class* pOtherObject = pField->GetAddress<Class>(pObject);
				if (ImGui::TreeNode(*pField->GetFieldName()))
				{
					for (unsigned int i = 0; i < fields.GetCursor(); i++)
					{
						DrawField(pOtherObject, fields[i]);
					}
					ImGui::TreePop();
				}
			}
		}

	}
	void DefaultComponentVisualizer::OnPaint()
	{
		Component* pComponent = GetComponent();

		const Array<Field*> fields = pComponent->GetType()->GetFields();

		for (unsigned int i = 0; i < fields.GetCursor(); i++)
		{
			const Field* pField = fields[i];

			DrawField(pComponent, pField);
		}
	}
}