#pragma once
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Runtime/Event/Event.h>
#include <Runtime/Graphics/Pipeline/Output/OutputDesc.h>

namespace Portakal
{
	class Framebuffer;
	class TextureResource;
	class GraphicsDevice;
	class ResourceTable;
	class Swapchain;

	/// <summary>
	/// A resource specialized in render targets
	/// </summary>
	PCLASS();
	class PORTAKAL_API RenderTargetResource : public ResourceSubObject
	{
		GENERATE_CLASS(RenderTargetResource,Virtual);
	public:
		/// <summary>
		/// Generates custom render target
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		/// <param name="colorTargetFormats"></param>
		/// <param name="depthStencilFormat"></param>
		/// <param name="colorTargetNames"></param>
		RenderTargetResource(const unsigned int width, const unsigned int height, const Array<TextureFormat>& colorTargetFormats, const TextureFormat depthStencilFormat,const Array<String>& colorTargetNames = {});

		/// <summary>
		/// Generates render target for target swapchain framebuffer
		/// </summary>
		/// <param name="pSwapchain"></param>
		RenderTargetResource(Swapchain* pSwapchain);
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
		/// Returns the output description of the underlying framebuffer
		/// </summary>
		/// <returns></returns>
		FORCEINLINE OutputDesc GetOutputDesc() const noexcept;

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

		/// <summary>
		/// Registers anew delegate to the state changed event of this render target
		/// </summary>
		/// <param name="del"></param>
		void RegisterStateChangedDelegate(const Delegate<void, RenderTargetResource*>& del);

		/// <summary>
		/// Removes the existing delegate from the state changed event of this render target
		/// </summary>
		/// <param name="del"></param>
		void RemoveStateChangedDelegate(const Delegate<void, RenderTargetResource*>& del);
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

		/// <summary>
		/// Signals that the state of this render target changed, invokes event.
		/// </summary>
		void SignalStateChangedEvent();

		virtual void DestroyCore() override;
	private:
		const bool mSwapchain;
		Event<void, RenderTargetResource*> mStateChangedEvent;
		GraphicsDevice* mDevice;
		Framebuffer* mFramebuffer;
		Array<TextureResource*> mColorTargets;
		TextureResource* mDepthStencilTarget;
	};


#include "RenderTargetResource.reflect.h"
}