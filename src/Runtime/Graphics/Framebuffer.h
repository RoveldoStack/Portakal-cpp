#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/OutputDesc.h>
#include <Runtime/Graphics/FramebufferCreateDesc.h>

namespace Portakal
{
	class Texture;
	class PORTAKAL_API Framebuffer : public GraphicsDeviceObject
	{
	public:
		FORCEINLINE FramebufferAttachmentDesc GetDepthStencilTarget() const noexcept { return mDepthStencilTarget; }
		FORCEINLINE unsigned int GetWidth() const noexcept { return mWidth; }
		FORCEINLINE unsigned int GetHeight() const noexcept { return mHeight; }

		FORCEINLINE virtual Array<FramebufferAttachmentDesc> GetColorTargets() const noexcept { return mColorTargets; };
		FORCEINLINE virtual OutputDesc GetOutputDesc() const noexcept { return mOutputDesc; }
		FORCEINLINE virtual bool IsSwapchain() const noexcept { return mSwapchain; }

		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::Framebuffer; }
	protected:
		/// <summary>
		/// Constructor for ext framebuffers
		/// </summary>
		/// <param name="desc"></param>
		Framebuffer(const FramebufferCreateDesc& desc,const bool bSwapchain);
		virtual ~Framebuffer() {}

		FORCEINLINE void SetWidth(const unsigned int width) { mWidth = width; }
		FORCEINLINE void SetHeight(const unsigned int height) { mHeight = height; }
	private:
		Array<FramebufferAttachmentDesc> mColorTargets;
		FramebufferAttachmentDesc mDepthStencilTarget;
		OutputDesc mOutputDesc;
		unsigned int mWidth;
		unsigned int mHeight;
		const bool mSwapchain;
	};
}