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

		FORCEINLINE Array<Texture*> GetColorTargets() const noexcept { return _colorTargets; }
		FORCEINLINE Texture* GetDepthStencilTarget() const noexcept { return _depthStencilTarget; }
		FORCEINLINE OutputDesc GetOutputDesc() const noexcept { return _outputDesc; }
		FORCEINLINE unsigned int GetWidth() const noexcept { return _width; }
		FORCEINLINE unsigned int GetHeight() const noexcept { return _height; }
		FORCEINLINE bool IsSwapchain() const noexcept { return _swapchain; }

		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::Framebuffer; }
	protected:
		Framebuffer(const FramebufferCreateDesc& desc);
		virtual ~Framebuffer();

		void UpdateSwapchainTargets(const unsigned int width,const unsigned int height,const Array<Texture*>& colorTargets,Texture* pDepthStencilTarget);
	private:
		Array<Texture*> _colorTargets;
		Texture* _depthStencilTarget;
		const OutputDesc _outputDesc;
		unsigned int _width;
		unsigned int _height;
		const bool _swapchain;
	};
}