#pragma once
#include <Runtime/Graphics/GraphicsBuffer.h>
#include <Runtime/DX12/Core.h>
#include <d3d12.h>

namespace Portakal
{
	class PORTAKAL_API DX12Buffer : public GraphicsBuffer
	{
	public:
		DX12Buffer(const GraphicsBufferCreateDesc& desc, DX12Device* pDevice);
		virtual ~DX12Buffer() override final;

		FORCEINLINE ID3D12Resource* GetDXResource() const noexcept { return mResource.Get(); }
		FORCEINLINE D3D12_VERTEX_BUFFER_VIEW GetDXVertexBufferView() const noexcept { return mVertexBufferView; }
		FORCEINLINE D3D12_INDEX_BUFFER_VIEW GetDXIndexBufferView() const noexcept { return mIndexBufferView; }
		FORCEINLINE D3D12_CONSTANT_BUFFER_VIEW_DESC GetDXConstantBufferView() const noexcept { return mConstantBufferView; }
	private:
		DXPTR<ID3D12Resource> mResource;
		D3D12_VERTEX_BUFFER_VIEW mVertexBufferView;
		D3D12_INDEX_BUFFER_VIEW mIndexBufferView;
		D3D12_CONSTANT_BUFFER_VIEW_DESC mConstantBufferView;

		// Inherited via GraphicsBuffer
		virtual void OnDestroy() override;
	};
}