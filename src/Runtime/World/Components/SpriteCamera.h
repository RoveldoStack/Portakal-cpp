#pragma once
#include <Runtime/World/Component.h>
#include <Runtime/Math/Color4.h>

namespace Portakal
{
	class RenderTarget;
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
	};

	START_GENERATE_TYPE(SpriteCamera);
	START_TYPE_PROPERTIES(SpriteCamera);
	REGISTER_BASE_TYPE(Component);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(SpriteCamera);
	END_GENERATE_TYPE(SpriteCamera);
}