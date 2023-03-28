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

		FORCEINLINE ID3D11RenderTargetView* GetDXCurrentRtv() const noexcept { return mRenderTargetViews[0].Get(); }
		virtual void OnDestroy() override;
		virtual unsigned int GetCurrentImageIndex() const noexcept override;
		virtual void SwapbuffersCore() override;
		virtual void ResizeCore(const unsigned int width, const unsigned int height) override;
	private:
		ComPtr<IDXGISwapChain> mSwapchain;
		Array<ComPtr<ID3D11RenderTargetView>> mRenderTargetViews;
		ComPtr<ID3D11DepthStencilView> mDepthStencilView;
	};
}