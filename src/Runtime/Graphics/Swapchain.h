#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Graphics/SwapchainCreateDesc.h>
namespace Portakal
{
	class Framebuffer;
	class PORTAKAL_API Swapchain : public GraphicsDeviceObject
	{
	public:
		FORCEINLINE Framebuffer* GetFramebuffer() const noexcept { return mFramebuffer; }
		FORCEINLINE TextureFormat GetColorFormat() const noexcept { return mColorFormat; }
		FORCEINLINE TextureFormat GetDepthStencilFormat() const noexcept { return mDepthStencilFormat; }
		FORCEINLINE unsigned int GetColorBufferCount() const noexcept { return mColorBufferCount; }
		FORCEINLINE unsigned int GetWidth() const noexcept { return mWidth; }
		FORCEINLINE unsigned int GetHeight() const noexcept { return mHeight; }
		FORCEINLINE virtual unsigned int GetCurrentImageIndex() const noexcept = 0;

		void Swapbuffers();
		void Resize(const unsigned int width,const unsigned int height);

		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override { return GraphicsDeviceObjectType::Swapchain; }
	protected:
		Swapchain(const SwapchainCreateDesc& desc) : mFramebuffer(nullptr),mColorFormat(desc.ColorFormat),mColorBufferCount(desc.ColorBufferCount),mDepthStencilFormat(desc.DepthStencilFormat),mWidth(desc.Width),mHeight(desc.Height) {}
		~Swapchain() = default;

		void SetFramebuffer(Framebuffer* pFramebuffer) { mFramebuffer = pFramebuffer; }

		virtual void SwapbuffersCore() = 0;
		virtual void ResizeCore(const unsigned int width, const unsigned int height) = 0;
	private:
		Framebuffer* mFramebuffer;
		const TextureFormat mColorFormat;
		const TextureFormat mDepthStencilFormat;
		const unsigned int mColorBufferCount;
		unsigned int mWidth;
		unsigned int mHeight;
	};
}