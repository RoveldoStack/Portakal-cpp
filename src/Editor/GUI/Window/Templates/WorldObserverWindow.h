#pragma once
#include <Editor/GUI/Window/EditorWindow.h>

namespace Portakal
{
	class Scene;
	class PORTAKAL_API WorldObserverWindow : public EditorWindow
	{
		GENERATE_CLASS(WorldObserverWindow);
	public:
		WorldObserverWindow() : mTargetScene(nullptr) {}
		~WorldObserverWindow() = default;

		virtual void OnShow() override;
		virtual void OnHide() override;
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPaint() override;
	private:
		void OnSceneChanged(Scene* pNewScene);
		void RenderScene(Scene* pScene);
	private:
		Scene* mTargetScene;
	};

	START_GENERATE_TYPE(WorldObserverWindow);
	START_TYPE_PROPERTIES(WorldObserverWindow);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(WorldObserverWindow);
	END_GENERATE_TYPE(WorldObserverWindow);
}