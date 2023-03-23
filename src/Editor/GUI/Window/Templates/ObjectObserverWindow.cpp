#include "ObjectObserverWindow.h"
#include <Editor/GUI/Object/EditorObjectVisualizer.h>
#include <Editor/GUI/Object/CustomEditorObjectAttribute.h>
#include <Runtime/Object/TaggedObject.h>
#include <Libs/ImGui/imgui.h>
#include <Editor/GUI/Object/EditorObjectAPI.h>

namespace Portakal
{
	
	void ObjectObserverWindow::OnSignalNewObject(Class* pObject)
	{
		if (mLock)
			return;
		if (pObject == nullptr)
			return;

		/*
		* First finalize the former visualizer(if any)
		*/
		if (mCurrentVisualizer != nullptr)
		{
			mCurrentVisualizer->OnFinalize();
			mCurrentVisualizer->_SetTargetObject(nullptr);
			delete mCurrentVisualizer;
			mCurrentVisualizer = nullptr;
		}

		/*
		* Try find visualizer type
		*/
		Type* pVisualizerType = nullptr;
		for (unsigned int i = 0; i < mVisualizerEntries.GetCursor(); i++)
		{
			const VisualizerEntry& entry = mVisualizerEntries[i];

			if (entry.pAttribute->GetTargetObjectType() == pObject->GetType())
			{
				pVisualizerType = entry.pType;
				break;
			}
		}

		if (pVisualizerType == nullptr)
			return;

		/*
		* Create visualizer
		*/
		mCurrentVisualizer = (EditorObjectVisualizer*)pVisualizerType->CreateDefaultHeapObject();
		mCurrentVisualizer->_SetTargetObject(pObject);
		mCurrentVisualizer->OnInitialize();

	}
	void ObjectObserverWindow::OnShow()
	{

	}
	void ObjectObserverWindow::OnHide()
	{

	}
	void ObjectObserverWindow::OnInitialize()
	{
		/*
		* Collect object visualizer types
		*/
		const Array<Type*> types = Assembly::GetProcessAssembly()->GetTypes();
		for (unsigned int i = 0; i < types.GetCursor(); i++)
		{
			Type* pType = types[i];

			/*
			* Validate type subclass
			*/
			if (!pType->IsSubClassOf(typeof(EditorObjectVisualizer)))
				continue;

			/*
			* Get attribute
			*/
			CustomEditorObjectAttribute* pAttribute = pType->GetAttribute<CustomEditorObjectAttribute>();
			if (pAttribute == nullptr || pAttribute->GetTargetObjectType() == nullptr)
				continue;

			mVisualizerEntries.Add({pType,pAttribute});
		}

		/*
		* Register
		*/
		EditorObjectAPI::RegisterWindow(this);

	}
	void ObjectObserverWindow::OnFinalize()
	{
		if (mCurrentVisualizer != nullptr)
		{
			mCurrentVisualizer->OnFinalize();
			mCurrentVisualizer->_SetTargetObject(nullptr);
			delete mCurrentVisualizer;
		}

		mVisualizerEntries.Clear();

		EditorObjectAPI::RemoveWindow(this);
	}
	void ObjectObserverWindow::OnPaint()
	{
		if (mCurrentVisualizer == nullptr)
		{
			ImGui::Text("There is no visualizer for this object");
			return;
		}

		mCurrentVisualizer->OnPaint();
	}
}