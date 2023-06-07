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
		* Get aspects
		*/
		DisplayAspect* pDisplayAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<DisplayAspect>();
		Renderer2DSceneAspect* pRendererAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<Renderer2DSceneAspect>();

		/*
		* Remove the former one from the display aspect
		*/
		if (mRenderTarget != nullptr)
			pDisplayAspect->RemoveDisplay(mRenderTarget);

		/*
		* Inform that anew render target has been replaced
		*/
		pRendererAspect->SignalCameraRenderTargetChanged(this,mRenderTarget,pRenderTarget);

		/*
		* Set as new
		*/
		pDisplayAspect->RegisterDisplay(pRenderTarget);
		mRenderTarget = pRenderTarget;

	}

	void SpriteCameraComponent::SetClearColor(const Color4& color)
	{
		mClearColor = color;

		/*
		* Get renderer aspect and validate
		*/
		Renderer2DSceneAspect* pAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<Renderer2DSceneAspect>();
		if (pAspect == nullptr)
			return;

		/*
		* Signal
		*/
		pAspect->SignalCameraPropertiesChanged(this);
	}

	void SpriteCameraComponent::SetOrthoSize(const float size)
	{
		mOrthoSize = size;

		/*
		* Get renderer aspect and validate
		*/
		Renderer2DSceneAspect* pAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<Renderer2DSceneAspect>();
		if (pAspect == nullptr)
			return;

		/*
		* Signal
		*/
		pAspect->SignalCameraPropertiesChanged(this);
	}

	void SpriteCameraComponent::SetPosition(const Vector2F value)
	{
		mPosition = value;

		/*
		* Get renderer aspect and validate
		*/
		Renderer2DSceneAspect* pAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<Renderer2DSceneAspect>();
		if (pAspect == nullptr)
			return;

		/*
		* Signal
		*/
		pAspect->SignalCameraTransformChanged(this);
	}


	void SpriteCameraComponent::SetRotation(const float value)
	{
		mRotation = value;

		/*
		* Get renderer aspect and validate
		*/
		Renderer2DSceneAspect* pAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<Renderer2DSceneAspect>();
		if (pAspect == nullptr)
			return;

		/*
		* Signal
		*/
		pAspect->SignalCameraTransformChanged(this);
	}

	void SpriteCameraComponent::OnInitialize()
	{
		/*
		* Get display aspect and validate
		*/
		DisplayAspect* pDisplayAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<DisplayAspect>();
		if (pDisplayAspect == nullptr)
			return;

		/*
		* Get display aspect and validate
		*/
		Renderer2DSceneAspect* pRendererAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<Renderer2DSceneAspect>();
		if (pRendererAspect == nullptr)
			return;

		/*
		* Register yourself to the renderer aspect
		*/
		RenderTargetResource* pRt = new RenderTargetResource(512,512,{TextureFormat::R8_G8_B8_A8_UNorm,TextureFormat::R8_G8_B8_A8_UNorm},TextureFormat::None,{"Color","UvColor"});
		SetRenderTarget(pRt);

		/*
		* Register component
		*/
		pRendererAspect->RegisterCamera(this);
	}
	void SpriteCameraComponent::OnFinalize()
	{
		/*
		* Get aspects
		*/
		DisplayAspect* pDisplayAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<DisplayAspect>();
		Renderer2DSceneAspect* pRendererAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<Renderer2DSceneAspect>();

		/*
		* Remove render target from the display
		*/
		if (mRenderTarget != nullptr)
			pDisplayAspect->RemoveDisplay(mRenderTarget);

		/*
		* Remove this camera from the renderer
		*/
		if (pRendererAspect != nullptr)
		{
			pRendererAspect->RemoveCamera(this);
		}
	}
	
}