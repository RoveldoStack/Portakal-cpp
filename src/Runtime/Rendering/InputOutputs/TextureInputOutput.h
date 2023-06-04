#pragma once
#include <Runtime/Rendering/RenderPassInputOutput.h>
#include <Runtime/Resource/Texture/TextureResource.h>

namespace Portakal
{
	class PORTAKAL_API TextureInputOutput : public RenderPassInputOutput
	{
	public:
		TextureInputOutput(const String& name, RenderPass* pOwnerPass);
		~TextureInputOutput();

		void SetTexture(TextureResource* pTexture) { mTexture = pTexture; }
		// Inherited via RenderPassInputOutput
		virtual void* GetIOData() const noexcept override { return mTexture; }
		virtual RenderPassInputOutputType GetIOType() const override { return RenderPassInputOutputType::Texture; }
		virtual void ForwardCore(void* pData) override;
	private:
		TextureResource* mTexture;
	};
}