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
		FORCEINLINE Texture* GetDepthStencilTarget() const noexcept { return _depthStencilTarget; }
		FORCEINLINE unsigned int GetWidth() const noexcept { return _width; }
		FORCEINLINE unsigned int GetHeight() const noexcept { return _height; }

		FORCEINLINE virtual Array<Texture*> GetColorTargets() const noexcept { return _colorTargets; };
		FORCEINLINE virtual OutputDesc GetOutputDesc() const noexcept { return _outputDesc; }
		FORCEINLINE virtual bool IsSwapchain() const noexcept { return false; }

		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::Framebuffer; }
	protected:
		/// <summary>
		/// Constructor for ext framebuffers
		/// </summary>
		/// <param name="desc"></param>
		Framebuffer(const FramebufferCreateDesc& desc);

		/// <summary>
		/// Constructor for swapchain framebuffer
		/// </summary>
		Framebuffer(const unsigned int width,const unsigned int height);
		virtual ~Framebuffer() {}

		FORCEINLINE void SetWidth(const unsigned int width) { _width = width; }
		FORCEINLINE void SetHeight(const unsigned int height) { _height = height; }
	private:
		Array<Texture*> _colorTargets;
		Texture* _depthStencilTarget;
		OutputDesc _outputDesc;
		unsigned int _width;
		unsigned int _height;
	};
}