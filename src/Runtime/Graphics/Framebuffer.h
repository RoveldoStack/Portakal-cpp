#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/OutputDesc.h>
#include <Runtime/Graphics/FramebufferCreateDesc.h>

namespace Portakal
{
	class Texture;

	/// <summary>
	/// Framebuffer is a simple container for the color targets and depth stencil target, you can bind to the output of the pipeline in order to render into
	/// </summary>
	class PORTAKAL_API Framebuffer : public GraphicsDeviceObject
	{
	public:
		/// <summary>
		/// Returns the depth stencil target
		/// </summary>
		/// <returns></returns>
		FORCEINLINE FramebufferAttachmentDesc GetDepthStencilTarget() const noexcept { return mDepthStencilTarget; }

		/// <summary>
		/// Returns the width
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetWidth() const noexcept { return mWidth; }

		/// <summary>
		/// Returns the height
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetHeight() const noexcept { return mHeight; }

		/// <summary>
		/// Returns the color targets
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual Array<FramebufferAttachmentDesc> GetColorTargets() const noexcept { return mColorTargets; };

		/// <summary>
		/// Returns the output description
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual OutputDesc GetOutputDesc() const noexcept { return mOutputDesc; }

		/// <summary>
		/// Returns whether its a swapchain or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual bool IsSwapchain() const noexcept { return mSwapchain; }

		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::Framebuffer; }
	protected:
		/// <summary>
		/// Constructor for ext framebuffers
		/// </summary>
		/// <param name="desc"></param>
		Framebuffer(const FramebufferCreateDesc& desc,const bool bSwapchain);
		virtual ~Framebuffer() {}

		/// <summary>
		/// Sets the width of the framebuffer
		/// </summary>
		/// <param name="width"></param>
		FORCEINLINE void SetWidth(const unsigned int width) { mWidth = width; }

		/// <summary>
		/// Sets the height of the framebuffer
		/// </summary>
		/// <param name="height"></param>
		FORCEINLINE void SetHeight(const unsigned int height) { mHeight = height; }

	protected:
		virtual void OnDestroy() override;
	private:
		Array<FramebufferAttachmentDesc> mColorTargets;
		FramebufferAttachmentDesc mDepthStencilTarget;
		OutputDesc mOutputDesc;
		unsigned int mWidth;
		unsigned int mHeight;
		const bool mSwapchain;
	};
}