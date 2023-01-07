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

		FORCEINLINE ID3D12Resource* GetDXResource() const noexcept { return _resource.Get(); }
		FORCEINLINE D3D12_VERTEX_BUFFER_VIEW GetDXVertexBufferView() const noexcept { return _vertexBufferView; }
		FORCEINLINE D3D12_INDEX_BUFFER_VIEW GetDXIndexBufferView() const noexcept { return _indexBufferView; }
		FORCEINLINE D3D12_CONSTANT_BUFFER_VIEW_DESC GetDXConstantBufferView() const noexcept { return _constantBufferView; }
	private:
		DXPTR<ID3D12Resource> _resource;
		D3D12_VERTEX_BUFFER_VIEW _vertexBufferView;
		D3D12_INDEX_BUFFER_VIEW _indexBufferView;
		D3D12_CONSTANT_BUFFER_VIEW_DESC _constantBufferView;
	};
}