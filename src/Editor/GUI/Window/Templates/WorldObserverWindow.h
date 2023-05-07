#pragma once
#include <Editor/GUI/Window/EditorWindow.h>

namespace Portakal
{
	class Scene;
	PCLASS();
	class PORTAKAL_API WorldObserverWindow : public EditorWindow
	{
		GENERATE_CLASS(WorldObserverWindow);
	private:
		static Array<WorldObserverWindow*> sWindows;
	public:
		static void SignalSceneChanged(Scene* pScene);
		static void SignalSceneSaved(Scene* pScene);
	public:
		WorldObserverWindow() : mTargetScene(nullptr),mSceneContentChanged(false) {}
		~WorldObserverWindow() = default;

		virtual void OnShow() override;
		virtual void OnHide() override;
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPaint() override;
	private:
		void OnSceneChanged(Scene* pNewScene);
		void OnSceneContentChanged();
		void SaveScene();
		void RenderScene(Scene* pScene);
	private:
		Array<Type*> mAvailableAspects;
		Scene* mTargetScene;
		bool mSceneContentChanged;
	};

#include "WorldObserverWindow.reflect.h"
}