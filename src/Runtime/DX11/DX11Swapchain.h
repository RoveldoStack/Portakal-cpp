#pragma once
#include <Runtime/Graphics/Swapchain.h>
#include <Runtime/DX11/Core.h>
#include <d3d11.h>
#include <dxgi.h>

namespace Portakal
{
	class PORTAKAL_API DX11Swapchain : public Swapchain
	{
	public:
		DX11Swapchain(const SwapchainCreateDesc& desc,DX11Device* pDevice);
		~DX11Swapchain();

		virtual void OnDestroy() override;
		virtual unsigned int GetCurrentImageIndex() const noexcept override;
		virtual void SwapbuffersCore() override;
		virtual void ResizeCore(const unsigned int width, const unsigned int height) override;
	private:
		DXPTR<IDXGISwapChain> mSwapchain;
	};
}