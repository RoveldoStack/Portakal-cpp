#pragma once
#include <Editor/GUI/Window/EditorWindow.h>
#include <Runtime/Containers/Array.h>
namespace Portakal
{
	class Scene;
	class DisplayAspect;
	class RenderTarget;
	class TextureResource;
	PCLASS();
	class PORTAKAL_API GameObserverWindow : public EditorWindow
	{
		GENERATE_CLASS(GameObserverWindow);
	public:
		GameObserverWindow(): mHasResizeRequest(false),mCurrentDisplay(nullptr),mTargetScene(nullptr) {}
		~GameObserverWindow() = default;
	private:

		// Inherited via EditorWindow
		virtual void OnShow() override;
		virtual void OnHide() override;
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPaint() override;
	private:
		void OnSceneChanged(Scene* pNewScene);
		void OnViewportChanged(const Vector2UI newSize);
		void OnDisplayChanged(RenderTarget* pDisplay);
		void OnResize();
		void ClearCurrentDisplayBindings();
		void GetCurrentTargets();
	private:
		Scene* mTargetScene;
		RenderTarget* mCurrentDisplay;
		Array<TextureResource*> mCurrentTargets;
		unsigned int mCurrentSelectedTargetIndex;
		Vector2UI mLastViewportSize;
		bool mHasResizeRequest;
	};

#include "GameObserverWindow.reflect.h"
}