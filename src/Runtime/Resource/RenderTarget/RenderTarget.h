#pragma once
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Resource/Texture/TextureResource.h>

namespace Portakal
{
	class Framebuffer;
	class TextureResource;
	class GraphicsDevice;
	class PORTAKAL_API RenderTarget : public ResourceSubObject
	{
		GENERATE_CLASS(RenderTarget);
	public:
		RenderTarget(const unsigned int width, const unsigned int height, const Array<TextureFormat>& colorTargetFormats, const TextureFormat depthStencilFormat);
		~RenderTarget();

		FORCEINLINE unsigned int GetWidth() const noexcept;
		FORCEINLINE unsigned int GetHeight() const noexcept;

		void Resize(const unsigned int width,const unsigned int height);
	private:
		void Delete();
		void CreateResources(const unsigned int width,const unsigned int height,const Array<TextureFormat>& colorTargetFormats,const TextureFormat depthStencilFormat);
		virtual void DestroyCore() override;
	private:
		GraphicsDevice* mDevice;
		Framebuffer* mFramebuffer;
		Array<TextureResource*> mColorTargets;
		TextureResource* mDepthStencilTarget;
		unsigned int mWidth;
		unsigned int mHeight;

	};

	START_GENERATE_TYPE(RenderTarget);
	START_TYPE_PROPERTIES(RenderTarget);
	REGISTER_BASE_TYPE(ResourceSubObject);
	END_TYPE_PROPERTIES;
	NO_DEFAULT_CONSTRUCTOR;
	END_GENERATE_TYPE(RenderTarget);
}