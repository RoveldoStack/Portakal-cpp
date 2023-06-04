#pragma once
#include <Runtime/World/Component.h>
#include <Runtime/Math/Vector2.h>
#include <Runtime/Resource/Texture/TextureResource.h>

namespace Portakal
{
	PCLASS();
	class PORTAKAL_API Transform2DComponent : public Component
	{
		GENERATE_CLASS(Transform2DComponent);
	public:
		Transform2DComponent() = default;
		~Transform2DComponent() = default;

		FORCEINLINE Vector2F GetPosition() const noexcept { return mPosition; }
		FORCEINLINE Vector2F GetScale() const noexcept { return mRotation; }
		FORCEINLINE float GetRotation() const noexcept { return mRotation; }

		FORCEINLINE void SetPosition(const Vector2F value) { mPosition = value; }
		FORCEINLINE void SetScale(const Vector2F value) { mScale = value; }
		FORCEINLINE void SetRotation(const float value) { mRotation = value; }
	private:
		// Inherited via Component
		virtual void OnAspectRemoved(SceneAspect* pAspect) override;

		// Inherited via Component
		virtual void DestroyCore() override;
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
	private:
		Vector2F mPosition;
		Vector2F mScale;
		float mRotation;



	};

#include "Transform2DComponent.reflect.h"
}