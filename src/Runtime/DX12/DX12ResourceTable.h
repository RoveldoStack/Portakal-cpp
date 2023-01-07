#pragma once
#include <Runtime/Graphics/GraphicsResourceTable.h>
#include <Runtime/DX12/Core.h>
#include <d3d12.h>

namespace Portakal
{
	class PORTAKAL_API DX12ResourceTable : public GraphicsResourceTable
	{
	public:
		DX12ResourceTable(const GraphicsResourceTableCreateDesc& desc, DX12Device* pDevice);
		virtual ~DX12ResourceTable() override;

		FORCEINLINE ID3D12DescriptorHeap* GetDXDescriptorHeap() const noexcept { return _descriptorHeap.Get(); }

	private:
		DXPTR<ID3D12DescriptorHeap> _descriptorHeap;
	};
}