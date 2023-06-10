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
		* Set new display
		*/
		pDisplayAspect->RegisterDisplay(pRenderTarget);

		/*
		* Register state changes
		*/
		LOG("START", "START");
		if (mRenderTarget != nullptr)
			mRenderTarget->RemoveStateChangedDelegate(GENERATE_MEMBER_DELEGATE1(this, SpriteCameraComponent::OnSignalRenderTargetStateChanged, void, RenderTargetResource*));

		if (pRenderTarget != nullptr)
			pRenderTarget->RegisterStateChangedDelegate(GENERATE_MEMBER_DELEGATE1(this, SpriteCameraComponent::OnSignalRenderTargetStateChanged, void, RenderTargetResource*));

		/*
		* Inform that anew render target has been replaced
		*/
		pRendererAspect->SignalCameraRenderTargetChanged(this,pRenderTarget);
		LOG("END", "END");
		mRenderTarget = pRenderTarget;
	}

	void SpriteCameraComponent::SetClearColor(const Color4& color)
	{
		/*
		* Validate
		*/
		if (mClearColor == color)
			return;

		/*
		* Set color as new
		*/
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
		/*
		* Validate
		*/
		if (mOrthoSize == size)
			return;

		/*
		* Set ortho size as new
		*/
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
		/*
		* Validate
		*/
		if (mPosition == value)
			return;

		/*
		* Set as new
		*/
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
		/*
		* Validate
		*/
		if (mRotation == value)
			return;

		/*
		* Set as new
		*/
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
		* Register component
		*/
		pRendererAspect->RegisterCamera(this);

		/*
		* Register yourself to the renderer aspect
		*/
		RenderTargetResource* pRt = new RenderTargetResource(512,512,{TextureFormat::R8_G8_B8_A8_UNorm,TextureFormat::R8_G8_B8_A8_UNorm},TextureFormat::None,{"Color","UvColor"});
		pRt->SetTagName("SprCamera");

		SetRenderTarget(pRt);
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

		/*
		* Remove listener
		*/
		if (mRenderTarget != nullptr)
			mRenderTarget->RemoveStateChangedDelegate(GENERATE_MEMBER_DELEGATE1(this, SpriteCameraComponent::OnSignalRenderTargetStateChanged, void, RenderTargetResource*));
	}

	void SpriteCameraComponent::OnSignalRenderTargetStateChanged(RenderTargetResource* pRenderTarget)
	{
		LOG("SpriteCameraComponent", "Render target state changed!!!");
		Renderer2DSceneAspect* pRendererAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<Renderer2DSceneAspect>();

		if (pRendererAspect == nullptr)
			return;

		pRendererAspect->SignalCameraPropertiesChanged(this);
	}
	
}