#include "SpriteCameraComponent.h"
#include <Runtime/World/Scene.h>
#include <Runtime/World/Entity.h>
#include <Runtime/World/Aspects/DisplayAspect.h>
#include <Runtime/Renderers/2DRenderer/Renderer2DSceneAspect.h>

namespace Portakal
{
	void SpriteCameraComponent::SetRenderTarget(RenderTargetResource* pRenderTarget)
	{
		/*
		* Validate if change is necessary
		*/
		if (mRenderTarget == pRenderTarget)
			return;

		/*
		* Remove the former one from the display aspect
		*/
		if (mRenderTarget != nullptr)
			mDisplayAspect->RemoveDisplay(mRenderTarget);

		/*
		* Set as new
		*/
		mDisplayAspect->RegisterDisplay(pRenderTarget);
		mRenderTarget = pRenderTarget;
	}

	void SpriteCameraComponent::OnInitialize()
	{
		/*
		* Get display aspect and validate
		*/
		mDisplayAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<DisplayAspect>();
		if (mDisplayAspect == nullptr)
			return;

		/*
		* Get display aspect and validate
		*/
		mRendererAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<Renderer2DSceneAspect>();
		if (mRendererAspect == nullptr)
			return;

		/*
		* Register yourself to the renderer aspect
		*/

	}
	void SpriteCameraComponent::OnFinalize()
	{
		/*
		* Remove yourself from the renderer aspect
		*/
		if (mRenderTarget != nullptr)
			mDisplayAspect->RemoveDisplay(mRenderTarget);

		mDisplayAspect = nullptr;
	}
	void SpriteCameraComponent::OnAspectRemoved(SceneAspect* pAspect)
	{

	}
}