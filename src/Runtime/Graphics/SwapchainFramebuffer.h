#pragma once
#include <Runtime/Graphics/Framebuffer.h>
#include "SwapchainFramebufferCreateDesc.h"

namespace Portakal
{
	class PORTAKAL_API SwapchainFramebuffer : public Framebuffer
	{
		friend class Window;
	public:
		SwapchainFramebuffer(const SwapchainFramebufferCreateDesc& desc) : Framebuffer(desc.Width,desc.Height), _bufferCount(desc.BufferCount),_swapchainColorFormat(desc.ColorFormat),_swapchainDepthStencilFormat(desc.DepthStencilFormat)
		{

		}
		virtual ~SwapchainFramebuffer() {}

		FORCEINLINE unsigned int GetBufferCount() const noexcept { return _bufferCount; }
		FORCEINLINE TextureFormat GetSwapchainColorFormat() const noexcept { return _swapchainColorFormat; }
		FORCEINLINE TextureFormat GetSwapchainDepthStencilFormat() const noexcept { return _swapchainDepthStencilFormat; }

		FORCEINLINE virtual OutputDesc GetOutputDesc() const noexcept override;
		FORCEINLINE virtual unsigned int GetCurrentBackBufferIndex() const noexcept = 0;
		FORCEINLINE virtual bool IsSwapchain() const noexcept override { return true; }
	protected:
		virtual void ResizeCore(const unsigned int width, const unsigned int height) = 0;
	private:
		void _Resize(const unsigned int width, const unsigned int height);
	private:
		const unsigned int _bufferCount;
		TextureFormat _swapchainColorFormat;
		TextureFormat _swapchainDepthStencilFormat;
	};
}