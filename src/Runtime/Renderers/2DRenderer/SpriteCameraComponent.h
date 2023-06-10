#pragma once
#include <Runtime/World/Component.h>
#include <Runtime/Resource/RenderTarget/RenderTargetResource.h>
#include <Runtime/Math/Color4.h>
#include <Runtime/Math/Vector2F.h>

namespace Portakal
{
	class Renderer2DSceneAspect;
	class DisplayAspect;

	PCLASS();
	class PORTAKAL_API SpriteCameraComponent : public Component
	{
		GENERATE_CLASS(SpriteCameraComponent);
	public:
		SpriteCameraComponent() : mRenderTarget(nullptr),mOrthoSize(3),mRotation(0),mClearColor(Color4::DarkBlue()) {}
		~SpriteCameraComponent() = default;

		FORCEINLINE RenderTargetResource* GetRenderTarget() const noexcept { return mRenderTarget; }
		FORCEINLINE Color4 GetClearColor() const noexcept { return mClearColor; }
		FORCEINLINE float GetOrthoSize() const noexcept { return mOrthoSize; }
		FORCEINLINE Vector2F GetPosition() const noexcept { return mPosition; }
		FORCEINLINE float GetRotation() const noexcept { return mRotation; }

		void SetRenderTarget(RenderTargetResource* pRenderTarget);
		void SetClearColor(const Color4& color);
		void SetOrthoSize(const float size);
		void SetPosition(const Vector2F value);
		void SetScale(const Vector2F value);
		void SetRotation(const float value);
	private:
		// Inherited via Component
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		void OnSignalRenderTargetStateChanged(RenderTargetResource* pRenderTarget);
	private:
		RenderTargetResource* mRenderTarget;
		Color4 mClearColor;
		float mOrthoSize;
		Vector2F mPosition;
		float mRotation;
	};

#include "SpriteCameraComponent.reflect.h"
}