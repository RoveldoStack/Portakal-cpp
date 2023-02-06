#pragma once
#include <Runtime/Graphics/Swapchain.h>
#include <Runtime/DX12/Core.h>
#include <d3d12.h>
#include <dxgi.h>
#include <dxgi1_4.h>
namespace Portakal
{
	class PORTAKAL_API DX12Swapchain : public Swapchain
	{
	public:
		DX12Swapchain(const SwapchainCreateDesc& desc, DX12Device* pDevice);
		~DX12Swapchain() = default;

		FORCEINLINE IDXGISwapChain3* GetDXSwapchain() const noexcept { return mSwapchain.Get(); }

	private:
		void CreateRtvs(DX12Device* pDevice);

		virtual unsigned int GetCurrentImageIndex() const noexcept override;
		virtual void SwapbuffersCore() override;
		virtual void ResizeCore(const unsigned int width, const unsigned int height) override;
	private:
		DXPTR<IDXGISwapChain3> mSwapchain;

		// Inherited via Swapchain
		virtual void OnDestroy() override;
	};
}