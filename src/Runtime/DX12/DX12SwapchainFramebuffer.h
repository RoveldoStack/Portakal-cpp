#pragma once
#include <Runtime/DX12/Core.h>
#include <Runtime/Graphics/SwapchainFramebuffer.h>
#include <dxgi.h>
#include <dxgi1_4.h>
#include <d3d12.h>
#include <Runtime/Graphics/SwapchainFramebufferCreateDesc.h>

namespace Portakal
{
	class Window;

	class PORTAKAL_API DX12SwapchainFramebuffer : public SwapchainFramebuffer
	{
	public:
		DX12SwapchainFramebuffer(const SwapchainFramebufferCreateDesc& desc, DX12Device* pDevice);
		virtual ~DX12SwapchainFramebuffer() override;

		virtual Array<Texture*> GetColorTargets() const noexcept override;
		FORCEINLINE ID3D12DescriptorHeap* GetDXDepthStencilHeapDescriptor() const noexcept { return _depthStencilTargetHeap.Get(); }
		FORCEINLINE IDXGISwapChain3* GetDXSwapchain() const noexcept { return _swapchain.Get(); }
		FORCEINLINE D3D12_CPU_DESCRIPTOR_HANDLE GetDXCurrentRenderTargetDescriptor() const noexcept;
	protected:
		virtual void ResizeCore(const unsigned int width, const unsigned int height) override;
		virtual unsigned int GetCurrentBackBufferIndex() const noexcept override;
	private:
		Array<Texture*> _colorTextures;
		DXPTR<IDXGISwapChain3> _swapchain;
		DXPTR<ID3D12DescriptorHeap> _renderTargetHeap;
		DXPTR<ID3D12DescriptorHeap> _depthStencilTargetHeap;

	};
}