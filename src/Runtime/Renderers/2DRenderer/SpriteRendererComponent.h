#pragma once
#include <Runtime/World/Component.h>
#include <Runtime/Resource/Material/MaterialResource.h>
#include <Runtime/Resource/Texture/TextureResource.h>

namespace Portakal
{
	PCLASS();
	class PORTAKAL_API SpriteRendererComponent : public Component
	{
		GENERATE_CLASS(SpriteRendererComponent);
	public:
		SpriteRendererComponent() = default;
		~SpriteRendererComponent() = default;

		FORCEINLINE MaterialResource* GetMaterial() const noexcept { return mMaterial; }
		FORCEINLINE TextureResource* GetTexture() const noexcept { return mTexture; }

		void SetMaterial(MaterialResource* pMaterial);
		void SetTexture(TextureResource* pTexture);
	private:
		// Inherited via Component
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		// Inherited via Component
		virtual void OnAspectRemoved(SceneAspect* pAspect) override;
	private:
		MaterialResource* mMaterial;
		TextureResource* mTexture;

	};

#include "SpriteRendererComponent.reflect.h"
}