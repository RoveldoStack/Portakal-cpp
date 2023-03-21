#pragma once
#include <Runtime/World/Component.h>
#include <Runtime/Math/Vector2.h>
#include <Runtime/Resource/Texture/TextureResource.h>

namespace Portakal
{
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

		// Inherited via Component
		virtual void DestroyCore() override;

		virtual void OnInitialize() override;

		virtual void OnFinalize() override;

		int mTestValue;
		Transform2DComponent* mTestComp;
	private:
		Vector2F mPosition;
		Vector2F mScale;
		float mRotation;

	};

	START_GENERATE_TYPE(Transform2DComponent);
	START_TYPE_PROPERTIES(Transform2DComponent);
	REGISTER_BASE_TYPE(Component);
	REGISTER_FIELD(Transform2DComponent,mTestValue, int, AccessSpecifier::Public);
	REGISTER_FIELD_SELF(Transform2DComponent, mTestComp, AccessSpecifier::Public);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(Transform2DComponent);
	END_GENERATE_TYPE(Transform2DComponent);
}