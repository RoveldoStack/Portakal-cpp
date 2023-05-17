#pragma once
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Resource/Texture/TextureResource.h>

namespace Portakal
{
	class Framebuffer;
	class TextureResource;
	class GraphicsDevice;
	class ResourceTable;

	/// <summary>
	/// A resource specialized in render targets
	/// </summary>
	PCLASS();
	class PORTAKAL_API RenderTargetResource : public ResourceSubObject
	{
		GENERATE_CLASS(RenderTargetResource,Virtual);
	public:
		RenderTargetResource(const unsigned int width, const unsigned int height, const Array<TextureFormat>& colorTargetFormats, const TextureFormat depthStencilFormat,const Array<String>& colorTargetNames = {});
		~RenderTargetResource();

		/// <summary>
		/// Returns the width
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetWidth() const noexcept;

		/// <summary>
		/// Returns the height
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetHeight() const noexcept;

		/// <summary>
		/// Returns the underlying framebuffer object
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Framebuffer* GetFramebuffer() const noexcept { return mFramebuffer; }

		/// <summary>
		/// REturns the color target textures
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<TextureResource*> GetColorTargets() const noexcept { return mColorTargets; }

		/// <summary>
		/// Returns the depth stencil target texture
		/// </summary>
		/// <returns></returns>
		FORCEINLINE TextureResource* GetDepthStencilTarget() const noexcept { return mDepthStencilTarget; }

		/// <summary>
		/// Resized the render target
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		void Resize(const unsigned int width,const unsigned int height);
	private:

		/// <summary>
		/// Deletes the contents
		/// </summary>
		void Delete();

		/// <summary>
		/// Creates the resources
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		/// <param name="colorTargetFormats"></param>
		/// <param name="depthStencilFormat"></param>
		void CreateResources(const unsigned int width,const unsigned int height,const Array<TextureFormat>& colorTargetFormats,const TextureFormat depthStencilFormat, const Array<String>& colorTargetNames);
		virtual void DestroyCore() override;
	private:
		GraphicsDevice* mDevice;
		Framebuffer* mFramebuffer;
		Array<TextureResource*> mColorTargets;
		TextureResource* mDepthStencilTarget;
		unsigned int mWidth;
		unsigned int mHeight;
	};


#include "RenderTargetResource.reflect.h"
}