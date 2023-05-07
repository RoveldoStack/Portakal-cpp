#pragma once
#include <Runtime/World/Component.h>
#include <Runtime/Math/Color4.h>

namespace Portakal
{
	class RenderTarget;
	PCLASS();
	class PORTAKAL_API SpriteCamera : public Component
	{
		GENERATE_CLASS(SpriteCamera);
	public:
		SpriteCamera() = default;
		~SpriteCamera() = default;

		FORCEINLINE RenderTarget* GetRenderTarget() const noexcept { return mTarget; }
		FORCEINLINE ColorRgbaF GetClearColor() const noexcept { return mClearColor; }

		FORCEINLINE void SetRenderTarget(RenderTarget* pTarget);
		FORCEINLINE void SetClearColor(const ColorRgbaF& clearColor) { mClearColor = clearColor; }

	private:
		// Inherited via Component
		virtual void DestroyCore() override;
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;

	private:
		RenderTarget* mTarget;
		ColorRgbaF mClearColor;
		float mNearPlane;
		float mFarPlane;
		float mOrthoSize;
	};

#include "SpriteCamera.reflect.h"
}