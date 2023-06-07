#pragma once
#include <Runtime/World/Component.h>
#include <Runtime/Resource/Material/MaterialResource.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Runtime/Math/Vector2F.h>

namespace Portakal
{
	PCLASS();
	class PORTAKAL_API SpriteRendererComponent : public Component
	{
		GENERATE_CLASS(SpriteRendererComponent);
	public:
		SpriteRendererComponent() : mPosition({ 0,0 }), mScale({ 1,1 }),mRotation(0),mMaterial(nullptr),mTexture(mTexture)
		{

		}
		~SpriteRendererComponent() = default;

		FORCEINLINE MaterialResource* GetMaterial() const noexcept { return mMaterial; }
		FORCEINLINE TextureResource* GetTexture() const noexcept { return mTexture; }
		FORCEINLINE Vector2F GetPosition() const noexcept { return mPosition; }
		FORCEINLINE Vector2F GetScale() const noexcept { return mScale; }
		FORCEINLINE float GetRotation() const noexcept { return mRotation; }
		

		void SetMaterial(MaterialResource* pMaterial);
		void SetTexture(TextureResource* pTexture);

		void SetPosition(const Vector2F value);
		void SetScale(const Vector2F value);
		void SetRotation(const float value);
	private:
		// Inherited via Component
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
	private:
		MaterialResource* mMaterial;
		TextureResource* mTexture;

		PFIELD();
		Vector2F mPosition;
		PFIELD();
		Vector2F mScale;
		float mRotation;

	};

#include "SpriteRendererComponent.reflect.h"
}