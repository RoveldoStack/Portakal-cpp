#pragma once
#include <Editor/GUI/Window/EditorWindow.h>
#include <Editor/GUI/Object/CustomEditorObjectAttribute.h>

namespace Portakal
{
	class EditorObjectVisualizer;
	PCLASS();
	class PORTAKAL_API ObjectObserverWindow : public EditorWindow
	{
		GENERATE_CLASS(ObjectObserverWindow);
	public:
		ObjectObserverWindow() : mCurrentVisualizer(nullptr),mLock(false) {}
		~ObjectObserverWindow() = default;

		FORCEINLINE bool IsLocked() const noexcept { return mLock; }

		void OnSignalNewObject(Class* pObject);
		void SetLock(const bool state) { mLock = state; }
	private:

		// Inherited via EditorWindow
		virtual void OnShow() override;
		virtual void OnHide() override;
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPaint() override;
	private:
		struct VisualizerEntry
		{
			Type* pType;
			CustomEditorObjectAttribute* pAttribute;
		};
	private:
		EditorObjectVisualizer* mCurrentVisualizer;
		Array<VisualizerEntry> mVisualizerEntries;
		bool mLock;
	};

#include "ObjectObserverWindow.reflect.h"
}