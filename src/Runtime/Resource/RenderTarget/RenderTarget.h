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
	class PORTAKAL_API RenderTarget : public ResourceSubObject
	{
		GENERATE_CLASS(RenderTarget);
	public:
		RenderTarget(const unsigned int width, const unsigned int height, const Array<TextureFormat>& colorTargetFormats, const TextureFormat depthStencilFormat);
		~RenderTarget();

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
		/// Returns the dedicated resource table for this render target
		/// </summary>
		/// <returns></returns>
		FORCEINLINE ResourceTable* GetIsolatedResourceTable() const noexcept { return mIsolatedResourceTable; }

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
		void CreateResources(const unsigned int width,const unsigned int height,const Array<TextureFormat>& colorTargetFormats,const TextureFormat depthStencilFormat);
		virtual void DestroyCore() override;
	private:
		GraphicsDevice* mDevice;
		Framebuffer* mFramebuffer;
		ResourceTable* mIsolatedResourceTable;
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