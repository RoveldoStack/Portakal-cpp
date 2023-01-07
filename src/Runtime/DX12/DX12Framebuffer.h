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
		virtual ~DX12Framebuffer() override;

		FORCEINLINE ID3D12DescriptorHeap* GetDXColorHeapDescriptor() const noexcept { return _colorDescriptorHeap.Get(); }
		FORCEINLINE ID3D12DescriptorHeap* GetDXDepthStencilHeapDescriptor() const noexcept { return _depthStencilDescriptorHeap.Get(); }
	private:
		DXPTR<ID3D12DescriptorHeap> _colorDescriptorHeap;
		DXPTR<ID3D12DescriptorHeap> _depthStencilDescriptorHeap;
	};
}