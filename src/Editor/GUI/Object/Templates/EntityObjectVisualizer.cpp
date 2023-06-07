#include "EntityObjectVisualizer.h"
#include <Runtime/World/Component.h>
#include <Libs/ImGui/imgui.h>
#include <Editor/GUI/Window/Templates/WorldObserverWindow.h>
#include <Editor/GUI/Component/EditorComponentVisualizer.h>
#include <Editor/GUI/Component/CustomEditorComponentAttribute.h>
#include <Editor/GUI/Component/Templates/DefaultComponentVisualizer.h>
#include <Editor/GUI/Component/Templates/SpriteCameraComponentVisualizer.h>

namespace Portakal
{
	void EntityObjectVisualizer::OnInitialize()
	{
		mEntity = (Entity*)GetTargetObject();

		/*
		* Collect components types
		*/
		const Array<Type*> types = Assembly::GetProcessAssembly()->GetTypes();
		for (unsigned int i = 0; i < types.GetCursor(); i++)
		{
			Type* pType = types[i];
			if (pType->IsSubClassOf(typeof(Component)))
			{
				mComponentTypes.Add(pType);
			}
		}

		/*
		* Collect component visualizers
		*/
		for (unsigned int i = 0; i < types.GetCursor(); i++)
		{
			Type* pType = types[i];

			if (!pType->IsSubClassOf(typeof(EditorComponentVisualizer)))
				continue;

			CustomEditorComponentAttribute* pAttribute = pType->GetAttribute<CustomEditorComponentAttribute>();
			if (pAttribute == nullptr)
				continue;

			if (!pAttribute->GetTargetType()->IsSubClassOf(typeof(Component)))
				continue;

			mVisualizerEntries.Add({pAttribute->GetTargetType(),pType});
		}
	}
	void EntityObjectVisualizer::OnPaint()
	{
		/*
		* Validate entity
		*/
		if (mEntity == nullptr || mEntity->IsDestroyed())
		{
			ImGui::Text("This entity is invalid or destroyed!");
			return;
		}

		/*
		* Draw title
		*/
		ImGui::Text(*mEntity->GetTagName());
		ImGui::Spacing();
		ImGui::Separator();

		/*
		* Create unregistered components
		*/
		const Array<Component*> components = mEntity->GetComponents();
		for (unsigned int i = 0; i < components.GetCursor(); i++)
		{
			Component* pComponent = components[i];

			/*
			* Validate if we have this component
			*/
			const int mapIndex = mVisualizerMap.FindIndex(pComponent);
			if (mapIndex == -1) // create new index
			{
				Type* pVisualizerType = GetVisualizerType(pComponent->GetType());
				if (pVisualizerType == nullptr)
				{
					// create default visualizer
					pVisualizerType = typeof(DefaultComponentVisualizer);
				}

				EditorComponentVisualizer* pVisualizer = (EditorComponentVisualizer*)pVisualizerType->CreateDefaultHeapObject();
				pVisualizer->_SetComponent(pComponent);
				pVisualizer->OnInitialize();

				mVisualizerMap.Register(pComponent, pVisualizer);
			}
			
		}

		/*
		* Remove deleted components
		*/
		for (unsigned int i = 0; i < mVisualizerMap.GetCursor(); i++)
		{
			const RegistryEntry<Component*, EditorComponentVisualizer*>& entry = mVisualizerMap[i];
			if (entry.Key == nullptr || entry.Value == nullptr)
				continue;

			if (!components.Has(entry.Key))
			{
				entry.Value->OnFinalize();
				entry.Value->_SetComponent(nullptr);
				delete entry.Value;

				mVisualizerMap.Remove(entry.Key);
				i--;
			}
		}

		/*
		* Draw
		*/
		for (unsigned int i = 0; i < mVisualizerMap.GetCursor(); i++)
		{
			const RegistryEntry<Component*, EditorComponentVisualizer*>& entry = mVisualizerMap[i];
			if (entry.Key == nullptr || entry.Key->IsDestroyed() || entry.Value == nullptr)
				continue;

			if (ImGui::CollapsingHeader(*(entry.Key->GetTagName() + "##" + Guid::ToString(entry.Key->GetID()))))
			{
				entry.Value->OnPaint();
			}
		}

		/*
		* Events
		*/
		if (ImGui::IsWindowFocused() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			ImGui::OpenPopup("CreateComponentPopup");
		}

		/*
		* Popups
		*/
		if (ImGui::BeginPopup("CreateComponentPopup"))
		{
			for (unsigned int i = 0; i < mComponentTypes.GetCursor(); i++)
			{
				Type* pType = mComponentTypes[i];

				if (ImGui::Selectable(*pType->GetTypeName()))
				{
					/*
					* Create component
					*/
					mEntity->CreateComponent(pType);
					WorldObserverWindow::SignalSceneChanged(mEntity->GetOwnerScene());
				}
			}

			ImGui::EndPopup();
		}
	}
	void EntityObjectVisualizer::OnFinalize()
	{

	}
	Type* EntityObjectVisualizer::GetVisualizerType(Type* pComponentType)
	{
		for (unsigned int i = 0; i < mVisualizerEntries.GetCursor(); i++)
		{
			const VisualizerEntry& entry = mVisualizerEntries[i];

			if (pComponentType == entry.pComponentType)
				return entry.pVisualizerType;
		}

		return nullptr;
	}
}