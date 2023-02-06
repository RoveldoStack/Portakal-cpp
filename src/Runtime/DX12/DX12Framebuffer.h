#pragma once
#include <Runtime/Graphics/Framebuffer.h>
#include <Runtime/DX12/Core.h>
#include <d3d12.h>

namespace Portakal
{
	class PORTAKAL_API DX12Framebuffer : public Framebuffer
	{
	public:
		DX12Framebuffer(const FramebufferCreateDesc& desc, DX12Device* pDevice);
		DX12Framebuffer(const FramebufferCreateDesc& desc, const DXPTR<ID3D12DescriptorHeap> colorHeap, const DXPTR<ID3D12DescriptorHeap> depthStencilHeap);
		virtual ~DX12Framebuffer() override;

		FORCEINLINE ID3D12DescriptorHeap* GetDXColorHeapDescriptor() const noexcept { return mColorHeap.Get(); }
		FORCEINLINE ID3D12DescriptorHeap* GetDXDepthStencilHeapDescriptor() const noexcept { return mDepthStencilHeap.Get(); }
	private:
		DXPTR<ID3D12DescriptorHeap> mColorHeap;
		DXPTR<ID3D12DescriptorHeap> mDepthStencilHeap;

		// Inherited via Framebuffer
		virtual void OnDestroy() override;
	};
}