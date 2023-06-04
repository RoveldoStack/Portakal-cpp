#pragma once
#include <Runtime/World/Component.h>
#include <Runtime/Resource/RenderTarget/RenderTargetResource.h>

namespace Portakal
{
	class Renderer2DSceneAspect;
	class DisplayAspect;

	PCLASS();
	class PORTAKAL_API SpriteCameraComponent : public Component
	{
		GENERATE_CLASS(SpriteCameraComponent);
	public:
		SpriteCameraComponent() = default;
		~SpriteCameraComponent() = default;

		FORCEINLINE RenderTargetResource* GetRenderTarget() const noexcept { return mRenderTarget; }
		void SetRenderTarget(RenderTargetResource* pRenderTarget);
	private:

		// Inherited via Component
		virtual void OnAspectRemoved(SceneAspect* pAspect) override;
		// Inherited via Component
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
	private:
		RenderTargetResource* mRenderTarget;
		DisplayAspect* mDisplayAspect;
		Renderer2DSceneAspect* mRendererAspect;
	};

#include "SpriteCameraComponent.reflect.h"
}