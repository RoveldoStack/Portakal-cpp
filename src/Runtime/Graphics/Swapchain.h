#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Graphics/SwapchainCreateDesc.h>
namespace Portakal
{
	class Framebuffer;

	/// <summary>
	/// Represents a swapchain for a window
	/// </summary>
	class PORTAKAL_API Swapchain : public GraphicsDeviceObject
	{
	public:

		/// <summary>
		/// Returns the framebuffer of the swapchain
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Framebuffer* GetFramebuffer() const noexcept { return mFramebuffer; }

		/// <summary>
		/// Returns the color format of the swapchain
		/// </summary>
		/// <returns></returns>
		FORCEINLINE TextureFormat GetColorFormat() const noexcept { return mColorFormat; }

		/// <summary>
		/// Returns the depth stencil format of the swapchain
		/// </summary>
		/// <returns></returns>
		FORCEINLINE TextureFormat GetDepthStencilFormat() const noexcept { return mDepthStencilFormat; }

		/// <summary>
		/// Returns the color buffer count
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetColorBufferCount() const noexcept { return mColorBufferCount; }

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
		/// Returns the current image index of swapchain which currently being rendered into
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual unsigned int GetCurrentImageIndex() const noexcept = 0;

		/// <summary>
		/// Swaps the swapchain buffers
		/// </summary>
		void Swapbuffers();

		/// <summary>
		/// Resizes the swapchain
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		void Resize(const unsigned int width,const unsigned int height);

		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override { return GraphicsDeviceObjectType::Swapchain; }
	protected:
		Swapchain(const SwapchainCreateDesc& desc) : mFramebuffer(nullptr),mColorFormat(desc.ColorFormat),mColorBufferCount(desc.ColorBufferCount),mDepthStencilFormat(desc.DepthStencilFormat),mWidth(desc.Width),mHeight(desc.Height) {}
		~Swapchain() = default;

		/// <summary>
		/// Sets the current framebuffer
		/// </summary>
		/// <param name="pFramebuffer"></param>
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